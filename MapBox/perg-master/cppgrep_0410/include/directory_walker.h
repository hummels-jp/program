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
        const fs::path& startPath, // Starting path for the directory traversal
        ThreadSafeQueue<fs::path>& outputQueue, // Thread-safe queue for file paths
        std::atomic<int>& foundCounter, // Counter for files found
        std::mutex& consoleMutex // For error reporting
        );

    // Returns true if the path is valid, otherwise false
    bool isValid() const;

    // Perform directory traversal
    void run();

private:
    fs::path start_path_; // Starting path
    ThreadSafeQueue<fs::path>& file_queue_; // Thread-safe file queue
    std::atomic<int>& files_found_count_; // File counter
    std::mutex& output_mutex_; // Mutex for console output
    bool is_valid_path_ = false; // Whether the path is valid
};

#endif // DIRECTORY_WALKER_H