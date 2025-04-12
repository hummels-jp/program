#include "file_search.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <iostream>
#include <mutex>
using namespace std;

std::mutex console_mutex;

// Constructor
FileSearch::FileSearch(const fs::path& directory, const SearchOption& options)
    : directory_(directory), options_(options) {}

// Convert a string to lowercase
std::string FileSearch::to_lowercase(const std::string& str) const {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// Search a single file
bool FileSearch::search_file(const fs::path& file_path, std::vector<SearchResult>& results) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::vector<std::regex> regex_patterns;
    if (options_.isUseRegex()) {
        regex::flag_type flags = std::regex::ECMAScript;
        if (options_.isIgnoreCase()) {
            flags |= std::regex::icase;
        }
        if (options_.isExtendedRegex()) { // If the -E option is enabled
            flags = std::regex::extended; // Use extended regular expressions
        }
        for (const auto& keyword : options_.getKeywords()) {
            regex_patterns.emplace_back(keyword, flags);
        }
    }

    bool found = false;
    int line_number = 0;
    int match_count = 0; // Used to count the number of matching lines

    while (std::getline(file, line)) {
        ++line_number;
        bool match = false;
        std::string matched_content;

        // Check if the line matches
        if (options_.isUseRegex()) {
            for (const auto& regex_pattern : regex_patterns) {
                std::smatch match_result;
                if (std::regex_search(line, match_result, regex_pattern)) {
                    match = true;
                    if (options_.isOutputOnlyMatch() && !match_result.empty()) { // If the -o option is enabled
                        matched_content = match_result.str(); // Extract the matching part
                    }
                    break; // Exit the loop if a match is found
                }
            }
        } else {
            for (const auto& keyword : options_.getKeywords()) {
                std::string line_to_check = options_.isIgnoreCase() ? to_lowercase(line) : line;
                std::string keyword_to_check = options_.isIgnoreCase() ? to_lowercase(keyword) : keyword;
                auto pos = line_to_check.find(keyword_to_check);
                if (pos != std::string::npos) {
                    match = true;
                    if (options_.isOutputOnlyMatch()) { // If the -o option is enabled
                        matched_content = line.substr(pos, keyword_to_check.length()); // Extract the matching part
                    }
                    break; // Exit the loop if a match is found
                }
            }
        }

        // Adjust logic based on the invert_match option
        if (options_.isInvertMatch() ? !match : match) {
            ++match_count; // Increment the match count
            if (options_.isListOnly()) { // If the -l option is enabled
                results.emplace_back(file_path, 0, ""); // Only record the file name
                return true; // Only need to record the file name once
            } else if (!options_.isCountOnly()) { // If the -c option is not enabled, record the matching line or part
                results.emplace_back(file_path, line_number, options_.isOutputOnlyMatch() ? matched_content : line);
            }
            found = true;
        }
    }

    // If the -c option is enabled, record the number of matching lines
    if (options_.isCountOnly() && match_count > 0) {
        results.emplace_back(file_path, match_count, ""); // Record the number of matching lines
    }

    // If the -L option is enabled and the file contains no matches
    if (options_.isListOnlyNonMatching() && !found) {
        results.emplace_back(file_path, 0, ""); // Only record the file name
        return true;
    }

    return found;
}

// Search files in a directory
void FileSearch::search_directory(std::vector<SearchResult>& results) {
    if (fs::is_regular_file(directory_)) {
        search_file(directory_, results);
    } else if (fs::is_directory(directory_)) {
        for (const auto& entry : fs::recursive_directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                std::lock_guard<std::mutex> lock(console_mutex);
                search_file(entry.path(), results);
            }
        }
    } else {
        std::cerr << "Error: " << directory_ << " is neither a file nor a directory." << std::endl;
    }
}