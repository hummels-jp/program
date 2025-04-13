#include "search_file.h"
#include <fstream>
#include <algorithm>

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

// Search for keywords in the file and return matching results
std::vector<SearchResult> SearchFile::grepInFile(const fs::path& filePath, const SearchOption& option) {
    std::vector<SearchResult> results;
    std::ifstream file(filePath);
    if (!file.is_open()) return results;

    std::string line;
    int line_number = 0;
    while (std::getline(file, line)) {
        ++line_number;
        std::string search_line = line;
        std::string search_keyword = option.getKeyword();

        // If case-insensitive, convert strings to lowercase
        if (!option.isCaseSensitive()) {
            std::transform(search_line.begin(), search_line.end(), search_line.begin(), ::tolower);
            std::transform(search_keyword.begin(), search_keyword.end(), search_keyword.begin(), ::tolower);
        }

        bool contains_keyword = (search_line.find(search_keyword) != std::string::npos);

        // Decide whether to add the result based on inverted match
        if (option.isInvertMatch() ? !contains_keyword : contains_keyword) {
            results.emplace_back(filePath, line_number, line);
        }
    }
    return results;
}