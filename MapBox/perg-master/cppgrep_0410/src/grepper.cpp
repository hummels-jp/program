#include "grepper.h"
#include "argument_parser.h"
#include "directory_walker.h"
#include "file_searcher.h"
#include "thread_safe_queue.h"
#include "result.h"
#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <optional> // For optional<SearchOptions>

// Grepper class constructor
int Grepper::run(int argc, char* argv[]) {
    ArgumentParser parser;
    std::optional<SearchOptions> optionsOpt = parser.parse(argc, argv);

    if (!optionsOpt) {
        return 1; // Error or help request handled by the parser
    }
    SearchOptions options = *optionsOpt; // Retrieve options from optional

    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Starting search with " << options.num_threads << " worker threads." << std::endl;
    if (options.ignore_case) std::cout << "Option: Ignore case" << std::endl;
    if (options.use_regex) std::cout << "Option: Use regular expressions" << std::endl;

    ThreadSafeQueue<fs::path> fileQueue; // Thread-safe file queue
    ThreadSafeQueue<Result> resultQueue; // Thread-safe result queue

    // --- Start threads ---
    std::vector<std::thread> workerThreads;
    workerThreads.reserve(options.num_threads);

    // Walker (producer) thread: finds files and adds them to the queue
    DirectoryWalker walker(options.directory, fileQueue, files_found_count_, output_mutex_);
    if (!walker.isValid()) return 1; // Exit if initial path check fails
    std::thread walkerThread(&DirectoryWalker::run, &walker);

    // Searcher (consumer) threads: process files from the queue
    for (unsigned int i = 0; i < options.num_threads; ++i) {
         // Each searcher gets references to the queue, counters, options, and mutex
         workerThreads.emplace_back(FileSearcher{options, fileQueue, resultQueue,
                                   files_processed_count_, matches_found_count_, output_mutex_});
    }

    // --- Process results (in the main thread) and wait ---
    // Wait for the walker to finish adding files
    walkerThread.join();
    // Walker calls fileQueue.finish() upon completion

    // Wait for searchers to finish processing
    for (auto& t : workerThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    // Mark that no more results will be produced
    resultQueue.finish();

    // Process and print results from the result queue
    Result foundResult;
    while (resultQueue.try_pop(foundResult)) {
         if (foundResult.file_path.empty()) continue; // Handle possible empty results
         std::cout << foundResult.file_path.string() << ":"
                   << foundResult.line_number << ":"
                   << foundResult.line_content << std::endl;
    }

    // --- Output statistics ---
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Search completed." << std::endl;
    std::cout << "Number of files found by walker: " << files_found_count_.load() << std::endl;
    std::cout << "Number of files processed by searchers: " << files_processed_count_.load() << std::endl;
    std::cout << "Number of matches found: " << matches_found_count_.load() << std::endl;
    std::cout << "Total time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}