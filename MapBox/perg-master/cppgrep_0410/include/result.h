#ifndef RESULT_H
#define RESULT_H

#include <filesystem>
#include <string>

// Search result structure
struct Result {
    std::filesystem::path file_path;     // File path
    int line_number;                     // Line number
    std::string line_content;            // Content of the matching line
};

#endif // RESULT_H