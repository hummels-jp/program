#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <filesystem>
#include <string>

class SearchResult {
public:
    // Constructor
    SearchResult(const std::filesystem::path& file_path, int line_number, const std::string& line_content)
        : file_path(file_path), line_number(line_number), line_content(line_content) {}

    // Get the file path
    const std::filesystem::path& getFilePath() const {
        return file_path;
    }

    // Get the line number
    int getLineNumber() const {
        return line_number;
    }

    // Get the matching line content
    const std::string& getLineContent() const {
        return line_content;
    }

    // Set the file path
    void setFilePath(const std::filesystem::path& path) {
        file_path = path;
    }

    // Set the line number
    void setLineNumber(int number) {
        line_number = number;
    }

    // Set the matching line content
    void setLineContent(const std::string& content) {
        line_content = content;
    }

private:
    std::filesystem::path file_path;     // File path
    int line_number;                     // Line number
    std::string line_content;            // Matching line content
};

#endif // SEARCH_RESULT_H