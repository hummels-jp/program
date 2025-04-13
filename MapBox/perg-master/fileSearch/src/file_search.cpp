#include "file_search.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <iostream>
#include <mutex>
using namespace std;

std::mutex console_mutex;

// Constructor
FileSearch::FileSearch(const fs::path& directory, const SearchOption& options)
    : directory_(directory), options_(options) {}

// Convert a string to lowercase
std::string FileSearch::to_lowercase(const std::string& str) const {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// Search a single file
bool FileSearch::search_file(const fs::path& file_path, std::vector<SearchResult>& results) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return false;
    }

    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        ++line_number;
        bool match = false;
        std::string matched_content;

        for (const auto& keyword : options_.getKeywords()) {
            std::string line_to_check = options_.isIgnoreCase() ? to_lowercase(line) : line;
            std::string keyword_to_check = options_.isIgnoreCase() ? to_lowercase(keyword) : keyword;

            // Debugging output
            std::cout << "Line: " << line_to_check << ", Keyword: " << keyword_to_check << std::endl;

            auto pos = line_to_check.find(keyword_to_check);
            if (pos != std::string::npos) {
                match = true;
                if (options_.isOutputOnlyMatch()) {
                    matched_content = line.substr(pos, keyword_to_check.length());
                }
                break; // Exit the loop if a match is found
            }
        }

        if (match) {
            cout << "Found match in file: " << file_path << ", Line: " << line_number << std::endl;
            results.emplace_back(file_path, line_number, options_.isOutputOnlyMatch() ? matched_content : line);
            
        }
    }

    return !results.empty();
}

// Search files in a directory
void FileSearch::search_directory(std::vector<SearchResult>& results) {
    if (fs::is_regular_file(directory_)) {
        search_file(directory_, results);
    } else if (fs::is_directory(directory_)) {
        for (const auto& entry : fs::recursive_directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                std::lock_guard<std::mutex> lock(console_mutex);
                search_file(entry.path(), results);
            }
        }
    } else {
        std::cerr << "Error: " << directory_ << " is neither a file nor a directory." << std::endl;
    }
}

void FileSearch::search_directory(const std::function<void(const fs::path&)>& callback) {
    if (fs::is_regular_file(directory_)) {
        callback(directory_);
    } else if (fs::is_directory(directory_)) {
        for (const auto& entry : fs::recursive_directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                callback(entry.path());
            }
        }
    } else {
        std::cerr << "Error: " << directory_ << " is neither a file nor a directory." << std::endl;
    }
}

void FileSearch::search_directory(const std::function<void(const fs::path&, std::vector<SearchResult>&)>& callback) 
{
    if (fs::is_regular_file(directory_)) {
        std::vector<SearchResult> results;
        callback(directory_, results);
    } else if (fs::is_directory(directory_)) {
        for (const auto& entry : fs::recursive_directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                std::vector<SearchResult> results;
                callback(entry.path(), results);
            }
        }
    } else {
        std::cerr << "Error: " << directory_ << " is neither a file nor a directory." << std::endl;
    }
}