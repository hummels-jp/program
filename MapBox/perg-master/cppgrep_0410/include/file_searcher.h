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

    void operator()();

private:
    void searchFile(const fs::path& file_path);
    bool prepareSearch(); 

    const SearchOptions& options_;
    ThreadSafeQueue<fs::path>& file_queue_;
    ThreadSafeQueue<Result>& result_queue_;
    std::atomic<int>& files_processed_count_;
    std::atomic<int>& matches_found_count_;
    std::mutex& output_mutex_; 

    std::regex pattern_;
    std::string query_lower_;
    bool regex_valid_ = true; 
};

#endif // FILE_SEARCHER_H