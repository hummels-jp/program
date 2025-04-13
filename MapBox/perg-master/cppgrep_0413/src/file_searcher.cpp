#include "file_searcher.h"
#include "utils.h" // For to_lower, is_likely_binary
#include <fstream>
#include <iostream> // For cout, cerr
#include <string>
#include <system_error> // For regex_error

// 更新构造函数 - 移除 resultQueue 参数
FileSearcher::FileSearcher(
    const SearchOptions& opts,
    ThreadSafeQueue<fs::path>& inputFileQueue,
    // ThreadSafeQueue<Result>& outputResultQueue, // <-- 移除
    std::atomic<int>& processedCounter,
    std::atomic<int>& matchCounter,
    std::mutex& consoleMutex)
    : options_(opts),
      file_queue_(inputFileQueue),
      // result_queue_(outputResultQueue), // <-- 移除
      files_processed_count_(processedCounter),
      matches_found_count_(matchCounter),
      output_mutex_(consoleMutex) {} // <-- 初始化列表更新

bool FileSearcher::prepareSearch() {
    if (options_.use_regex) {
        try {
            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
            if (options_.ignore_case) {
                flags |= std::regex_constants::icase;
            }
            pattern_ = std::regex(options_.query, flags);
        } catch (const std::regex_error& e) {
            std::lock_guard<std::mutex> lock(output_mutex_); // 错误报告需要锁
            static bool error_reported = false; // 只报告一次正则错误
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
        return; // Exit if regex is invalid
    }

    fs::path current_file;
    while (file_queue_.try_pop(current_file)) {
         // If try_pop returned true but path is empty, it might be a spurious wake-up
         // or queue was empty but not finished yet. Just loop again.
        if (current_file.empty()) {
            if(file_queue_.is_finished()) break; // Double check if finished
            continue;
        }
        searchFile(current_file);
        current_file.clear(); // Good practice
    }
}

void FileSearcher::searchFile(const fs::path& file_path) {
    std::ifstream file_stream(file_path, std::ios::binary);
    if (!file_stream.is_open()) {
        return;
    }

    std::string line;
    int line_number = 0;
    try {
        while (std::getline(file_stream, line)) {
            line_number++;
            if (Utils::is_likely_binary(line)) {
                break;
            }

            bool match_found = false;
            if (options_.use_regex) {
                 if (!regex_valid_) continue; // Skip if regex was invalid
                match_found = std::regex_search(line, pattern_);
            } else if (options_.ignore_case) {
                match_found = Utils::to_lower(line).find(query_lower_) != std::string::npos;
            } else {
                match_found = line.find(options_.query) != std::string::npos;
            }

            if (match_found) { 
                // --- 修改核心：直接打印 ---
                {
                    std::lock_guard<std::mutex> lock(output_mutex_); // 锁住控制台输出
                    std::cout << file_path.string() << ":"
                              << line_number << ":"
                              << line << std::endl;
                } // 锁在此处自动释放
                matches_found_count_++; // 原子操作，无需锁
            }
        }
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(output_mutex_); // 错误日志仍需锁
        std::cerr << "Error reading file " << file_path << ": " << e.what() << std::endl;
    }
    files_processed_count_++; // 原子操作，无需锁
}