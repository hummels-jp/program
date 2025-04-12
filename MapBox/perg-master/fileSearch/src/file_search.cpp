#include "file_search.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <iostream>
#include <mutex>
using namespace std;

std::mutex console_mutex;

// 构造函数
FileSearch::FileSearch(const fs::path& directory, const SearchOption& options)
    : directory_(directory), options_(options) {}

// 转换字符串为小写
std::string FileSearch::to_lowercase(const std::string& str) const {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// 搜索单个文件
bool FileSearch::search_file(const fs::path& file_path, std::vector<SearchResult>& results) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::vector<std::regex> regex_patterns;
    if (options_.isUseRegex()) {
        regex::flag_type flags = std::regex::ECMAScript;
        if (options_.isIgnoreCase()) {
            flags |= std::regex::icase;
        }
        if (options_.isExtendedRegex()) { // 如果启用了 -E 选项
            flags = std::regex::extended; // 使用扩展正则表达式
        }
        for (const auto& keyword : options_.getKeywords()) {
            regex_patterns.emplace_back(keyword, flags);
        }
    }

    bool found = false;
    int line_number = 0;
    int match_count = 0; // 用于统计匹配的行数

    while (std::getline(file, line)) {
        ++line_number;
        bool match = false;
        std::string matched_content;

        // 判断是否匹配
        if (options_.isUseRegex()) {
            for (const auto& regex_pattern : regex_patterns) {
                std::smatch match_result;
                if (std::regex_search(line, match_result, regex_pattern)) {
                    match = true;
                    if (options_.isOutputOnlyMatch() && !match_result.empty()) { // 如果启用了 -o 选项
                        matched_content = match_result.str(); // 提取匹配的部分
                    }
                    break; // 如果匹配成功，跳出循环
                }
            }
        } else {
            for (const auto& keyword : options_.getKeywords()) {
                std::string line_to_check = options_.isIgnoreCase() ? to_lowercase(line) : line;
                std::string keyword_to_check = options_.isIgnoreCase() ? to_lowercase(keyword) : keyword;
                auto pos = line_to_check.find(keyword_to_check);
                if (pos != std::string::npos) {
                    match = true;
                    if (options_.isOutputOnlyMatch()) { // 如果启用了 -o 选项
                        matched_content = line.substr(pos, keyword_to_check.length()); // 提取匹配的部分
                    }
                    break; // 如果匹配成功，跳出循环
                }
            }
        }

        // 根据 invert_match 选项调整逻辑
        if (options_.isInvertMatch() ? !match : match) {
            ++match_count; // 增加匹配计数
            if (options_.isListOnly()) { // 如果启用了 -l 选项
                results.emplace_back(file_path, 0, ""); // 只记录文件名
                return true; // 只需要记录一次文件名即可
            } else if (!options_.isCountOnly()) { // 如果不是 -c 选项，记录匹配的行或匹配的部分
                results.emplace_back(file_path, line_number, options_.isOutputOnlyMatch() ? matched_content : line);
            }
            found = true;
        }
    }

    // 如果启用了 -c 选项，记录匹配的行数
    if (options_.isCountOnly() && match_count > 0) {
        results.emplace_back(file_path, match_count, ""); // 记录匹配的行数
    }

    // 如果启用了 -L 选项，并且文件中没有匹配内容
    if (options_.isListOnlyNonMatching() && !found) {
        results.emplace_back(file_path, 0, ""); // 只记录文件名
        return true;
    }

    return found;
}

// 搜索目录中的文件
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