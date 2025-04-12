#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <filesystem>
#include <string>

class SearchResult {
public:
    // 构造函数
    SearchResult(const std::filesystem::path& file_path, int line_number, const std::string& line_content)
        : file_path(file_path), line_number(line_number), line_content(line_content) {}

    // 获取文件路径
    const std::filesystem::path& getFilePath() const {
        return file_path;
    }

    // 获取行号
    int getLineNumber() const {
        return line_number;
    }

    // 获取匹配的行内容
    const std::string& getLineContent() const {
        return line_content;
    }

    // 设置文件路径
    void setFilePath(const std::filesystem::path& path) {
        file_path = path;
    }

    // 设置行号
    void setLineNumber(int number) {
        line_number = number;
    }

    // 设置匹配的行内容
    void setLineContent(const std::string& content) {
        line_content = content;
    }

private:
    std::filesystem::path file_path;     // 文件路径
    int line_number;                     // 行号
    std::string line_content;            // 匹配的行内容
};

#endif // SEARCH_RESULT_H