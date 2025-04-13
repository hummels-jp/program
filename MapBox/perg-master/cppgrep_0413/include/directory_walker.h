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
    fs::path start_path_;
    ThreadSafeQueue<fs::path>& file_queue_;
    std::atomic<int>& files_found_count_;
    std::mutex& output_mutex_;
    bool is_valid_path_ = false;
};

#endif // DIRECTORY_WALKER_H