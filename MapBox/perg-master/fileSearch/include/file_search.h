#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <filesystem>
#include <string>
#include <vector>
#include <functional>
#include "search_result.h"
#include "search_option.h"

namespace fs = std::filesystem;

class FileSearch {
public:
    // Constructor
    FileSearch(const fs::path& directory, const SearchOption& options);

    // Search files in the directory
    void search_directory(std::vector<SearchResult>& results);

    // Search files in the directory with a callback
    void search_directory(const std::function<void(const fs::path&)>& callback);

    // Search files in the directory with a callback that includes results
    void search_directory(const std::function<void(const fs::path&, std::vector<SearchResult>&)>& callback);

    // Search a single file
    bool search_file(const fs::path& file_path, std::vector<SearchResult>& results);

    // Convert a string to lowercase
    std::string to_lowercase(const std::string& str) const;
private:
    fs::path directory_;       // Directory path to search
    SearchOption options_;     // Search options
};

#endif // FILE_SEARCH_H