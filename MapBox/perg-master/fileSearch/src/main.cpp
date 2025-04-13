#include "file_search.h"
#include "search_option.h"
#include "search_result.h"
#include "ThreadPool.h" // Include the ThreadPool header
#include <iostream>
#include <regex>
#include <vector>
#include <thread>
#include <mutex>
#include <future> // Include for std::future

int main(int argc, char* argv[]) {
    // Parse command-line arguments using SearchOption::parseArguments
    SearchOption options = SearchOption::parseArguments(argc, argv);

    // Create a FileSearch object
    FileSearch file_search(options.getDirectoryPath(), options);

    // Store search results
    std::vector<SearchResult> results;
    std::mutex results_mutex;

    // Create a thread pool
    ThreadPool thread_pool(std::thread::hardware_concurrency());

    // Declare a vector to store futures
    std::vector<std::future<void>> futures;

    try {
        // Perform the search asynchronously
        file_search.search_directory([&](const fs::path& file_path, std::vector<SearchResult>& local_results) {
            futures.push_back(thread_pool.enqueue([&]() {
                if (file_search.search_file(file_path, local_results)) {
                    std::lock_guard<std::mutex> lock(results_mutex);
                    results.insert(results.end(), local_results.begin(), local_results.end());
                }
            }));
        });

        // Wait for all tasks to complete
        for (auto& future : futures) {
            future.get();
        }

        // Output all results
        for (const auto& result : results) {
            std::cout << "File: " << result.getFilePath();
            if (options.isCountOnly() || options.isListOnly() || options.isListOnlyNonMatching()) {
                std::cout << std::endl;
                continue;
            }
            std::cout << ", Line: " << result.getLineNumber();

            // Check if the --color option is enabled
            if (options.isHighlightMatch()) {
                // Highlight matching keywords using regular expressions
                std::string content = result.getLineContent();
                for (const auto& keyword : options.getKeywords()) {
                    std::regex keyword_regex(keyword, options.isIgnoreCase() ? std::regex::icase : std::regex::ECMAScript);
                    content = std::regex_replace(content, keyword_regex, "\033[1;31m$&\033[0m");
                }
                std::cout << "  Content: " << content << std::endl;
            } else {
                std::cout << "  Content: " << result.getLineContent() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}