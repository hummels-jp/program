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
    // Check if the path exists and is valid, file or directory
    if (!fs::exists(start_path_)) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error: Path does not exist: " << start_path_.string() << std::endl;
        is_valid_path_ = false;
    } else {
        is_valid_path_ = true;
    }
}

// if the path is valid, it will be set to true, get the private member
bool DirectoryWalker::isValid() const {
    return is_valid_path_;
}

// This function will traverse the directory and add files to the queue
void DirectoryWalker::run() {
    if (!is_valid_path_) return;

    try 
    {
        // Check if the path is a regular file or a directory
        // If it's a file, add it to the queue
        if (fs::is_regular_file(start_path_)) {
            file_queue_.push(start_path_);
            files_found_count_++;
        } 
        // If it's a directory, traverse it recursively
        else if (fs::is_directory(start_path_)) 
        {
            // Use recursive_directory_iterator to traverse the directory
            // Use skip_permission_denied to skip files with permission errors
            // This option is available in C++17 and later
            auto options = fs::directory_options::skip_permission_denied;
            for (const auto& entry : fs::recursive_directory_iterator(start_path_, options)) 
            {
                try {
                    if (fs::is_regular_file(entry.path())) {
                        file_queue_.push(entry.path());
                        files_found_count_++;
                    }
                } catch (const fs::filesystem_error& e) 
                {
                    std::lock_guard<std::mutex> lock(output_mutex_);
                    std::cerr << "Error accessing entry " << entry.path() << ": " << e.what() << std::endl;
                }
               
            }
        }
        // If it's neither a file nor a directory, report an error 
        else {
             std::lock_guard<std::mutex> lock(output_mutex_);
             std::cerr << "Error: Path is not a regular file or directory: "
                       << start_path_.string() << std::endl;
        }
    }
    // Handle exceptions for filesystem operations 
    catch (const fs::filesystem_error& e) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Error during directory traversal: " << e.what() << std::endl;
    } 
    // Handle other exceptions that may occur
    catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(output_mutex_);
        std::cerr << "Unexpected error during traversal: " << e.what() << std::endl;
    }
    // Mark the queue as finished after processing
    file_queue_.finish();
}