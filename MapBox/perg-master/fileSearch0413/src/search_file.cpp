#include "search_file.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <memory> // For std::unique_ptr

// Recursively find all files in the directory
std::vector<fs::path> SearchFile::findFiles(const fs::path& directory) {
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    return files;
}

/**
 * @brief Search for keywords in the specified file and return matching results.
 *
 * This function reads the file line by line and searches for the specified keyword.
 * - If case-insensitive search is enabled, both the keyword and file content are converted to lowercase.
 * - If inverted match is enabled, lines not containing the keyword are included in the results.
 * - If the file cannot be opened or is empty, an empty result set is returned.
 *
 * @param filePath The path to the file to search.
 * @param option Search options, including the keyword, case sensitivity, and inverted match flag.
 * @return A vector of SearchResult objects containing the file path, line number, and matching line content.
 */
std::vector<SearchResult> SearchFile::searchInFile(const fs::path& filePath, const SearchOption& option) {
    // Helper function to determine match condition
    auto matchesCondition = [](bool keyword_found, bool invert_match) {
        return invert_match ? !keyword_found : keyword_found;
    };

    std::vector<SearchResult> results;

    // Use unique_ptr to manage the file stream
    auto file = std::make_unique<std::ifstream>(filePath);

    // Check if the file was successfully opened
    if (!file->is_open()) {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return results;
    }

    std::string line;
    size_t line_number = 0;
    std::string search_keyword = option.getKeyword();

    // Convert the keyword to lowercase if case-insensitive
    if (!option.isCaseSensitive()) {
        std::transform(search_keyword.begin(), search_keyword.end(), search_keyword.begin(), ::tolower);
    }

    while (std::getline(*file, line)) {
        ++line_number;
        std::string search_line = line;

        // Convert the line to lowercase if case-insensitive
        if (!option.isCaseSensitive()) {
            std::transform(search_line.begin(), search_line.end(), search_line.begin(), ::tolower);
        }

        // Check if the keyword is found in the line
        bool keyword_found = (search_line.find(search_keyword) != std::string::npos);

        // Use a helper function to decide whether to add the result
        if (matchesCondition(keyword_found, option.isInvertMatch())) {
            results.emplace_back(filePath, line_number, line);
        }
    }

    // No need to explicitly close the file; unique_ptr will handle it
    return results;
}