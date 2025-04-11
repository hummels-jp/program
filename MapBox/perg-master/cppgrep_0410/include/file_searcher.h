#ifndef FILE_SEARCHER_H
#define FILE_SEARCHER_H

#include "options.h"
#include "thread_safe_queue.h"
#include "result.h"
#include <filesystem>
#include <atomic>
#include <mutex>
#include <regex>
namespace fs = std::filesystem;

class FileSearcher {
public:
    FileSearcher(
        const SearchOptions& opts,
        ThreadSafeQueue<fs::path>& inputFileQueue,
        ThreadSafeQueue<Result>& outputResultQueue,
        std::atomic<int>& processedCounter,
        std::atomic<int>& matchCounter,
        std::mutex& consoleMutex 
    );

    void operator()(); // This function is called when the object is used as a thread

private:
    void searchFile(const fs::path& file_path); //  Searches a single file
    bool prepareSearch();  // Prepares the search by compiling the regex and converting the query to lowercase

    const SearchOptions& options_; // Search options
    ThreadSafeQueue<fs::path>& file_queue_;  // Thread-safe queue for input files
    ThreadSafeQueue<Result>& result_queue_; // Thread-safe queue for output results
    std::atomic<int>& files_processed_count_; // Number of files processed
    std::atomic<int>& matches_found_count_; // Number of matches found
    std::mutex& output_mutex_;  // Mutex for console output

    std::regex pattern_; // Regular expression pattern for searching
    std::string query_lower_; // Lowercase version of the search query
    bool regex_valid_ = true; // Indicates if the regex is valid
};

#endif // FILE_SEARCHER_H