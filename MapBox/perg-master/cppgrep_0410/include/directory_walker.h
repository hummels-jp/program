#ifndef DIRECTORY_WALKER_H
#define DIRECTORY_WALKER_H

#include "thread_safe_queue.h"
#include <filesystem>
#include <atomic>
#include <mutex>

namespace fs = std::filesystem;

class DirectoryWalker {
public:
    DirectoryWalker(
        const fs::path& startPath,
        ThreadSafeQueue<fs::path>& outputQueue,
        std::atomic<int>& foundCounter,
        std::mutex& consoleMutex // 用于错误报告
        );

    // 返回true如果路径有效，否则返回false
    bool isValid() const;

    // 执行目录遍历
    void run();

private:
    fs::path start_path_; // 起始路径
    ThreadSafeQueue<fs::path>& file_queue_; // 线程安全的文件队列
    std::atomic<int>& files_found_count_; // 文件计数器
    std::mutex& output_mutex_; // 互斥锁用于控制台输出
    bool is_valid_path_ = false; // 路径是否有效
};

#endif // DIRECTORY_WALKER_H