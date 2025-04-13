#ifndef RESULT_H
#define RESULT_H

#include <filesystem>
#include <string>

// 搜索结果结构体
struct Result {
    std::filesystem::path file_path;     // 文件路径
    int line_number;                     // 行号
    std::string line_content;            // 匹配行的内容
};

#endif // RESULT_H