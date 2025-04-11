#include "directory_walker.h"
#include <iostream> // For cerr


DirectoryWalker::DirectoryWalker(
    const fs::path& startPath, 
    ThreadSafeQueue<fs::path>& outputQueue,
    std::atomic<int>& foundCounter,
    std::mutex& consoleMutex)
    : start_path_(startPath),
      file_queue_(outputQueue),
      files_found_count_(foundCounter),
      output_mutex_(consoleMutex)
{
    if (!fs::exists(start_path_)) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error: Path does not exist: " << start_path_.string() << std::endl;
        is_valid_path_ = false;
    } else {
        is_valid_path_ = true;
    }
}

// 返回true如果路径有效，否则返回false
// 如果路径是一个常规文件或目录，则返回true
bool DirectoryWalker::isValid() const {
    return is_valid_path_;
}

void DirectoryWalker::run() {
    if (!is_valid_path_) return;

    try {
        if (fs::is_regular_file(start_path_)) {
            file_queue_.push(start_path_);
            files_found_count_++;
        } else if (fs::is_directory(start_path_)) {
            auto options = fs::directory_options::skip_permission_denied;
            for (const auto& entry : fs::recursive_directory_iterator(start_path_, options)) {
                try {
                    if (fs::is_regular_file(entry.path())) {
                        file_queue_.push(entry.path());
                        files_found_count_++;
                    }
                } catch (const fs::filesystem_error& e) {
                    std::lock_guard<std::mutex> lock(output_mutex_);
                    std::cerr << "Error accessing entry " << entry.path() << ": " << e.what() << std::endl;
                }
               
            }
        } else {
             std::lock_guard<std::mutex> lock(output_mutex_);
             std::cerr << "Error: Path is not a regular file or directory: "
                       << start_path_.string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error during directory traversal: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Unexpected error during traversal: " << e.what() << std::endl;
    }

    file_queue_.finish();
}