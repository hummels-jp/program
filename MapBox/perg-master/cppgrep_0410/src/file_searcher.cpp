#include "file_searcher.h"
#include "utils.h" // For to_lower, is_likely_binary
#include <fstream>
#include <iostream> // For cerr
#include <string>
#include <system_error> // For regex_error

FileSearcher::FileSearcher(
    const SearchOptions& opts,
    ThreadSafeQueue<fs::path>& inputFileQueue,
    ThreadSafeQueue<Result>& outputResultQueue,
    std::atomic<int>& processedCounter,
    std::atomic<int>& matchCounter,
    std::mutex& consoleMutex)
    : options_(opts),
      file_queue_(inputFileQueue),
      result_queue_(outputResultQueue),
      files_processed_count_(processedCounter),
      matches_found_count_(matchCounter),
      output_mutex_(consoleMutex) {}

// 准备搜索
// 通过编译正则表达式和将查询转换为小写来准备搜索
// 如果正则表达式无效，则返回false
// 如果正则表达式有效，则返回true
bool FileSearcher::prepareSearch() {
    // 该函数在每个线程中调用一次
    // 仅在使用正则表达式时编译正则表达式
    // 如果使用正则表达式，则编译正则表达式
    if (options_.use_regex) 
    {
        try {
            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
            if (options_.ignore_case) {
                flags |= std::regex_constants::icase;
            }
            pattern_ = std::regex(options_.query, flags);
        } catch (const std::regex_error& e) {
            // Error reported only once by the first thread attempting this
            std::lock_guard<std::mutex> lock(output_mutex_);
            static bool error_reported = false;
            if (!error_reported) {
                 std::cerr << "Error: Invalid regular expression: " << e.what() << std::endl;
                 error_reported = true;
            }
            regex_valid_ = false;
            return false;
        }
    } 
    else if (options_.ignore_case) {
        query_lower_ = Utils::to_lower(options_.query);
    }
    return true;
}

// 线程函数
// 该函数在每个线程中调用一次
// 该函数从输入队列中弹出文件路径并搜索文件
// 如果文件路径为空，则检查完成状态
// 如果完成状态为true，则退出循环
// 如果完成状态为false，则继续弹出文件路径
// 如果文件路径不为空，则搜索文件
void FileSearcher::operator()() {
    if (!prepareSearch() && options_.use_regex) {
        return; // Exit if the regular expression is invalid
    }

    fs::path current_file;
    // try_pop returns true when popping an item or when the queue is empty but not yet finished
    while (file_queue_.try_pop(current_file)) {
        if (current_file.empty()) {
             // Spurious wakeup or notified before the finished flag is fully set?
             // Explicitly check the finished state again
             if (file_queue_.is_finished()) break;
             continue; // Queue is empty, retry
        }
        searchFile(current_file);
        current_file.clear(); // Reset for the next iteration
    }
}

// 搜索文件
// 读取文件的每一行并检查是否匹配
// 如果找到匹配项，则将结果推送到结果队列
// 如果文件无法打开，则跳过该文件
// 如果文件是二进制文件，则跳过该文件
// 如果读取文件时发生错误，则记录错误
// 使用共享互斥锁进行控制台输出
// 读取文件的每一行并检查是否匹配
// 如果找到匹配项，则将结果推送到结果队列
void FileSearcher::searchFile(const fs::path& file_path) 
{
    // read the file in binary mode
    std::ifstream file_stream(file_path, std::ios::binary);
    if (!file_stream.is_open()) {
        return; // Skip files we can't open
    }

    std::string line;
    int line_number = 0;
    try {
        while (std::getline(file_stream, line)) {
            line_number++;
            if (Utils::is_likely_binary(line)) {
                break; // Skip likely binary files
            }
            bool match_found = false;
            if (options_.use_regex) {
                match_found = std::regex_search(line, pattern_);
            } else if (options_.ignore_case) {
                match_found = Utils::to_lower(line).find(query_lower_) != std::string::npos;
            } else {
                match_found = line.find(options_.query) != std::string::npos;
            }

            if (match_found) {
                result_queue_.push({file_path, line_number, line});
                matches_found_count_++;
            }
        }
    } catch (const std::exception& e) {
        // Log errors while reading the file - use shared mutex for console output
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error reading file " << file_path << ": " << e.what() << std::endl;
    }
    files_processed_count_++;
}