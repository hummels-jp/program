#ifndef SEARCH_FILE_H
#define SEARCH_FILE_H

#include <filesystem>
#include <string>
#include <vector>
#include "search_result.h"
#include "search_option.h"

namespace fs = std::filesystem;

class SearchFile {
public:
    // Constructor
    SearchFile() = default;

    // Recursively find all files in the directory
    std::vector<fs::path> findFiles(const fs::path& directory);

    // Search for keywords in the file and return matching results
    std::vector<SearchResult> grepInFile(const fs::path& filePath, const SearchOption& option);
};

#endif // SEARCH_FILE_H