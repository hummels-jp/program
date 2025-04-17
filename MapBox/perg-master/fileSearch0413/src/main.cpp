#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <future>
#include <regex> // Include regex library
#include "ThreadPool.h"
#include "search_result.h"
#include "search_option.h"
#include "search_file.h" // Include SearchFile class

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // Check the number of arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <path> <keyword> [-i] [-v] [-n] [-l] [-c] [-o] [-E]" << std::endl;
        return 1;
    }

    // Parse command-line arguments
    std::string inputPath = argv[1];       // Path
    std::string keyword = argv[2];         // Keyword
    bool caseSensitive = true;             // Default: case-sensitive
    bool invertMatch = false;              // Default: no inverted match
    bool showLineNumber = false;           // Default: do not show line numbers
    bool listOnly = false;                 // Default: do not list only file names
    bool countOnly = false;                // Default: do not show only the count of matching lines
    bool onlyMatch = false;                // Default: do not show only the matched string
    bool useRegex = false;                 // Default: do not use regex

    // Check for -i, -v, -n, -l, -c, -o, and -E options
    for (int i = 3; i < argc; ++i) {
        if (std::string(argv[i]) == "-i") {
            caseSensitive = false;
        } else if (std::string(argv[i]) == "-v") {
            invertMatch = true;
        } else if (std::string(argv[i]) == "-n") {
            showLineNumber = true;
        } else if (std::string(argv[i]) == "-l") {
            listOnly = true;
        } else if (std::string(argv[i]) == "-c") {
            countOnly = true;
        } else if (std::string(argv[i]) == "-o") {
            onlyMatch = true;
        } else if (std::string(argv[i]) == "-E") {
            useRegex = true;
        }
    }

    // Create search options
    SearchOption option(keyword, caseSensitive, invertMatch, showLineNumber, listOnly, countOnly, onlyMatch, useRegex);

    // Get the singleton instance of the thread pool
    ThreadPool& pool = ThreadPool::getInstance(std::thread::hardware_concurrency() * 2);

    SearchFile searchFile; // Create SearchFile object
    std::vector<fs::path> files;

    // Determine if the input path is a file or a directory
    if (fs::is_regular_file(inputPath)) {
        files.push_back(inputPath); // If it's a file, add it directly to the file list
    } else if (fs::is_directory(inputPath)) {
        files = searchFile.findFiles(inputPath); // If it's a directory, recursively find all files
    } else {
        std::cerr << "Invalid path: " << inputPath << std::endl;
        return 1;
    }

    // Perform grep operations asynchronously
    // Create a vector to store futures for each file
    // This allows us to run grepInFile in parallel
    // and collect results later

    std::vector<std::future<std::vector<SearchResult>>> futures;
    for (const auto& file : files) {
        // Use a lambda function to capture the file and option
        // and pass them to the grepInFile method
        // 
        futures.emplace_back(pool.enqueue([&searchFile, file, &option]() {
            return searchFile.searchInFile(file, option);
        }));
    }

    // Store all matching results
    // block until all futures are ready
    // and collect the results into a single vector
    // the first file is very big, the main thread will wait for it to finish,
    std::vector<SearchResult> allResults;
    for (auto& future : futures) {
        auto search_results = future.get();
        allResults.insert(allResults.end(), search_results.begin(), search_results.end());
    }

    // While there are still unfinished futures， loop until all futures are ready
// while (!futures.empty()) {
//     for (auto it = futures.begin(); it != futures.end();) {
//         // Check if the future is ready
//         if (it->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
//             // Get the result and add it to allResults
//             auto search_results = it->get();
//             allResults.insert(allResults.end(), search_results.begin(), search_results.end());

//             // Remove the completed future from the list
//             it = futures.erase(it);
//         } else {
//             ++it; // Move to the next future
//         }
//     }

//     // Optionally, sleep for a short duration to reduce CPU usage
//     std::this_thread::sleep_for(std::chrono::milliseconds(10));
// }

    // Output matching results
    for (const auto& result : allResults) {
        std::string lineContent = result.getLineContent();

        if (option.isOnlyMatch()) {
            // If the -o option is enabled, output only the matched string
            std::cout << lineContent << std::endl;
        } else {
            // Default: output detailed matching information
            std::cout << "Found in: " << result.getFilePath();
            if (option.isShowLineNumber()) {
                std::cout << " (Line " << result.getLineNumber() << ")";
            }
            std::cout << ": " << lineContent << std::endl;
        }
    }

    return 0;
}