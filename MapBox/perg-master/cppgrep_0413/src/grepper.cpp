#include "grepper.h"
#include "argument_parser.h"
#include "directory_walker.h"
#include "file_searcher.h"
#include "thread_safe_queue.h"
// #include "result.h" // <-- 移除
#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <optional> // For optional<SearchOptions>
#include <filesystem> // Include filesystem header

namespace fs = std::filesystem; // Define alias for convenience

int Grepper::run(int argc, char* argv[]) {
    ArgumentParser parser;
    std::optional<SearchOptions> optionsOpt = parser.parse(argc, argv);

    if (!optionsOpt) {
        return 1; // Error or help request handled by parser
    }
    SearchOptions options = *optionsOpt; // Get options from optional

    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Starting search, using " << options.num_threads << " worker threads." << std::endl;
    if (options.ignore_case) std::cout << "Option: Ignore case" << std::endl;
    if (options.use_regex) std::cout << "Option: Use regular expression" << std::endl;

    ThreadSafeQueue<fs::path> fileQueue;
    // ThreadSafeQueue<Result> resultQueue; // <-- 移除

    // --- Start Threads ---
    std::vector<std::thread> workerThreads;
    workerThreads.reserve(options.num_threads);

    // Walker (Producer) Thread
    DirectoryWalker walker(options.directory, fileQueue, files_found_count_, output_mutex_);
    if (!walker.isValid()) return 1; // Exit if initial path check failed
    std::thread walkerThread(&DirectoryWalker::run, &walker);

    // Searcher (Consumer) Threads
    for (unsigned int i = 0; i < options.num_threads; ++i) {
         // 更新 FileSearcher 构造调用，移除 resultQueue
         workerThreads.emplace_back(FileSearcher{options, fileQueue, /* REMOVED resultQueue */
                                   files_processed_count_, matches_found_count_, output_mutex_});
    }

    // --- Wait for Threads ---
    // Wait for walker to finish adding files (it calls fileQueue.finish())
    if (walkerThread.joinable()) {
        walkerThread.join();
    }

    // Now wait for searchers to finish processing all items from fileQueue
    for (auto& t : workerThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    // resultQueue.finish(); // <-- 移除

    // 移除结果处理循环:
    // Result foundResult;
    // while (resultQueue.try_pop(foundResult)) { ... } // <-- 整个循环移除
    // 结果现在由 FileSearcher 直接打印

    // --- Output Stats ---
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Final output barrier to ensure stats appear after all result lines
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Search completed." << std::endl;
    std::cout << "Files found by walker: " << files_found_count_.load() << std::endl;
    std::cout << "Files processed by searchers: " << files_processed_count_.load() << std::endl;
    std::cout << "Matches found: " << matches_found_count_.load() << std::endl;
    std::cout << "Total time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}