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
    // 默认构造函数
    SearchFile() = default;

    // 递归查找目录中的所有文件
    std::vector<fs::path> findFiles(const fs::path& directory);

    // 在文件中搜索关键字并返回匹配结果
    std::vector<SearchResult> searchInFile(const fs::path& filePath, const SearchOption& option);

private:
    // 辅助函数：检查是否匹配条件
    bool matchesCondition(bool keyword_found, bool invert_match) const;
};

#endif // SEARCH_FILE_H