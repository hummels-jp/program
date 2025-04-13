#ifndef OPTIONS_H
#define OPTIONS_H

#include <filesystem>
#include <string>

// 搜索参数配置结构体
struct SearchOptions {
    std::string query;                    // 搜索词或正则表达式
    std::filesystem::path directory;      // 搜索目录路径
    bool ignore_case = false;            // 是否忽略大小写
    bool use_regex = false;              // 是否使用正则表达式
    unsigned int num_threads = 2;         // 工作线程数
};

#endif // OPTIONS_H