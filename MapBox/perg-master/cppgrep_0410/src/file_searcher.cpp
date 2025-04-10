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

bool FileSearcher::prepareSearch() {
    if (options_.use_regex) {
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
    } else if (options_.ignore_case) {
        query_lower_ = Utils::to_lower(options_.query);
    }
    return true;
}

void FileSearcher::operator()() {
    if (!prepareSearch() && options_.use_regex) {
        return; // 如果正则表达式无效则退出
    }

    fs::path current_file;
    // try_pop在弹出项目时或队列为空但未完成时返回true
    while (file_queue_.try_pop(current_file)) {
        if (current_file.empty()) {
             // 虚假唤醒或在完成标志完全设置前被notify_all唤醒？
             // 再次显式检查完成状态
             if (file_queue_.is_finished()) break;
             continue; // 队列为空，重试
        }
        searchFile(current_file);
        current_file.clear(); // 为下一次迭代重置
    }
}

void FileSearcher::searchFile(const fs::path& file_path) {
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
                break; // 跳过可能的二进制文件
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
        // 记录读取文件时的错误 - 使用共享互斥锁进行控制台输出
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "读取文件时出错 " << file_path << ": " << e.what() << std::endl;
    }
    files_processed_count_++;
}