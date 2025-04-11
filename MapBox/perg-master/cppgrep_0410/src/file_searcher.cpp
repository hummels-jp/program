#include "file_searcher.h"
#include "utils.h" // For to_lower, is_likely_binary
#include <fstream>
#include <iostream> // For cerr
#include <string>
#include <system_error> // For regex_error

// Constructor
FileSearcher::FileSearcher(
    const SearchOptions& opts,
    ThreadSafeQueue<fs::path>& inputFileQueue,
    ThreadSafeQueue<Result>& outputResultQueue,
    std::atomic<int>& processedCounter,
    std::atomic<int>& matchCounter,
    std::mutex& consoleMutex)
    : options_(opts),
      file_queue_(inputFileQueue),
      result_queue_(outputResultQueue),
      files_processed_count_(processedCounter),
      matches_found_count_(matchCounter),
      output_mutex_(consoleMutex) {}

// Prepare for search
// Prepare the search by compiling the regular expression and converting the query to lowercase
// Returns false if the regular expression is invalid
// Returns true if the regular expression is valid
bool FileSearcher::prepareSearch() {
    // This function is called once in each thread
    // Compile the regular expression only when using regex
    if (options_.use_regex) 
    {
        try {
            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
            if (options_.ignore_case) {
                flags |= std::regex_constants::icase;
            }
            pattern_ = std::regex(options_.query, flags);
        } catch (const std::regex_error& e) {
            // Error reported only once by the first thread attempting this
            std::lock_guard<std::mutex> lock(output_mutex_);
            static bool error_reported = false;
            if (!error_reported) {
                 std::cerr << "Error: Invalid regular expression: " << e.what() << std::endl;
                 error_reported = true;
            }
            regex_valid_ = false;
            return false;
        }
    } 
    else if (options_.ignore_case) {
        query_lower_ = Utils::to_lower(options_.query);
    }
    return true;
}

// Thread function
// This function is called once in each thread
// This function pops file paths from the input queue and searches the files
// If the file path is empty, check the finished state
// If the finished state is true, exit the loop
// If the finished state is false, continue popping file paths
// If the file path is not empty, search the file
void FileSearcher::operator()() {
    if (!prepareSearch() && options_.use_regex) {
        return; // Exit if the regular expression is invalid
    }

    fs::path current_file;
    // try_pop returns true when popping an item or when the queue is empty but not yet finished
    while (file_queue_.try_pop(current_file)) {
        if (current_file.empty()) {
             // Spurious wakeup or notified before the finished flag is fully set?
             // Explicitly check the finished state again
             if (file_queue_.is_finished()) break;
             continue; // Queue is empty, retry
        }
        searchFile(current_file);
        current_file.clear(); // Reset for the next iteration
    }
}

// Search file
// Read each line of the file and check for matches
// If a match is found, push the result to the result queue
// Skip the file if it cannot be opened
// Skip the file if it is a binary file
// Log errors if an error occurs while reading the file
// Use a shared mutex for console output
void FileSearcher::searchFile(const fs::path& file_path) 
{
    // Read the file i
    // std::ifstream file_stream(file_path, std::ios::binary);
    std::ifstream file_stream(file_path, std::ios::in);
    if (!file_stream.is_open()) {
        return; // Skip files we can't open
    }

    std::string line;
    int line_number = 0;
    try {
        while (std::getline(file_stream, line)) {
            line_number++;
            if (Utils::is_likely_binary(line)) {
                break; // Skip likely binary files
            }
            bool match_found = false;
            if (options_.use_regex) {
                match_found = std::regex_search(line, pattern_);
            } else if (options_.ignore_case) {
                match_found = Utils::to_lower(line).find(query_lower_) != std::string::npos;
            } else {
                match_found = line.find(options_.query) != std::string::npos;
            }

            if (match_found) {
                result_queue_.push({file_path, line_number, line});
                matches_found_count_++;
            }
        }
    } catch (const std::exception& e) {
        // Log errors while reading the file - use shared mutex for console output
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error reading file " << file_path << ": " << e.what() << std::endl;
    }
    files_processed_count_++;
}