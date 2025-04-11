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
        std::mutex& consoleMutex // For error reporting
        );

    // Returns true if the path is valid, otherwise false
    bool isValid() const;

    // Perform directory traversal
    void run();

private:
    fs::path start_path_;
    ThreadSafeQueue<fs::path>& file_queue_;
    std::atomic<int>& files_found_count_;
    std::mutex& output_mutex_;
    bool is_valid_path_ = false;
};

#endif // DIRECTORY_WALKER_H