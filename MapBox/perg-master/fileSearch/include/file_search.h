#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <filesystem>
#include <string>
#include <vector>
#include "search_result.h"
#include "search_option.h"

namespace fs = std::filesystem;

class FileSearch {
public:
    // 构造函数
    FileSearch(const fs::path& directory, const SearchOption& options);

    // 搜索目录中的文件
    void search_directory(std::vector<SearchResult>& results);

private:
    // 搜索单个文件
    bool search_file(const fs::path& file_path, std::vector<SearchResult>& results);

    // 转换字符串为小写
    std::string to_lowercase(const std::string& str) const;

    fs::path directory_;       // 搜索的目录路径
    SearchOption options_;     // 搜索选项
};

#endif // FILE_SEARCH_H