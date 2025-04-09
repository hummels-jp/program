#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem> 
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <stdexcept> 
#include <chrono>
#include <regex> 
#include <algorithm> 
using namespace std;


namespace fs = std::filesystem;

// 程序选项结构体
struct SearchOptions {
    std::string query;
    fs::path directory;
    bool ignore_case = false;
    bool use_regex = false;
};

// 线程安全队列的实现，用于多线程间的任务分发
template <typename T>
class ThreadSafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_var_.notify_one();
    }

    // 尝试从队列中获取一个值，如果队列为空且已完成则返回false
    bool try_pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this] { return !queue_.empty() || finished_; });

        if (queue_.empty() && finished_) {
            return false;
        }

        if (queue_.empty()) {
           return false;
        }

        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // 标记队列已完成，通知所有等待线程
    void finish() {
        std::lock_guard<std::mutex> lock(mutex_);
        finished_ = true;
        cond_var_.notify_all();
    }

    bool is_finished() const {
         std::lock_guard<std::mutex> lock(mutex_);
         return finished_ && queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;
    std::atomic<bool> finished_{false};
};

// 全局变量声明
ThreadSafeQueue<fs::path> file_queue;        // 文件路径队列
std::mutex output_mutex;                     // 输出互斥锁
std::atomic<int> files_processed_count{0};   // 已处理文件计数
std::atomic<int> matches_found_count{0};     // 匹配数计数

// 转换字符串为小写
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// 文件搜索工作线程函数
void search_file_worker(const SearchOptions& options) {
    fs::path file_path;
    
    // 预编译正则表达式（如果启用）
    std::regex pattern;
    std::string query_lower;
    
    if (options.use_regex) {
        try {
            std::regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript;
            if (options.ignore_case) {
                flags |= std::regex_constants::icase;
            }
            pattern = std::regex(options.query, flags);
        } catch (const std::regex_error& e) {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cerr << "Error: Invalid regular expression: " << e.what() << std::endl;
            return;
        }
    } else if (options.ignore_case) {
        // 如果忽略大小写但不使用正则表达式，预先转换查询字符串
        query_lower = to_lower(options.query);
    }
    
    while (file_queue.try_pop(file_path)) {
        std::ifstream file_stream(file_path, std::ios::binary);

        if (!file_stream.is_open()) {
            continue;
        }

        std::string line;
        int line_number = 0;
        try {
            while (std::getline(file_stream, line)) {
                line_number++;
                 // 检测是否为二进制文件
                 bool is_likely_binary = false;
                 for(char c : line) {
                    if (!isprint(static_cast<unsigned char>(c)) && !std::isspace(static_cast<unsigned char>(c))) {
                       is_likely_binary = true;
                       break;
                    }
                 }
                 if (is_likely_binary) {
                     break;
                 }

                // 根据选项进行匹配搜索
                bool match_found = false;
                if (options.use_regex) {
                    // 使用正则表达式搜索
                    match_found = std::regex_search(line, pattern);
                } else if (options.ignore_case) {
                    // 忽略大小写的搜索
                    std::string line_lower = to_lower(line);
                    match_found = line_lower.find(query_lower) != std::string::npos;
                } else {
                    // 原始的区分大小写搜索
                    match_found = line.find(options.query) != std::string::npos;
                }

                // 查找匹配并输出结果
                if (match_found) {
                    std::lock_guard<std::mutex> lock(output_mutex);
                    std::cout << file_path.string() << ":" << line_number << ":" << line << std::endl;
                    matches_found_count++;
                }
            }
        } catch (const std::exception& e) {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cerr << "Error reading file " << file_path << ": " << e.what() << std::endl;
        }
        files_processed_count++;
    }
}

// 显示帮助信息
void show_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options] <query> <directory path>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i        Ignore case" << std::endl;
    std::cout << "  -r        Use regular expression for search" << std::endl;
    std::cout << "  -h        Show this help information" << std::endl;
}

int main(int argc, char* argv[]) 
{
    // 使用选项结构体
    SearchOptions options;
    
    // 解析命令行参数
    int arg_index = 1;
    while (arg_index < argc && argv[arg_index][0] == '-') {
        std::string option = argv[arg_index];
        if (option == "-i") {
            options.ignore_case = true;
        } else if (option == "-r") {
            options.use_regex = true;
        } else if (option == "-h") {
            show_usage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown option: " << option << std::endl;
            show_usage(argv[0]);
            return 1;
        }
        arg_index++;
    }
    
    // 检查参数
    if (argc - arg_index != 2) {
        std::cerr << "Error: Insufficient or too many arguments" << std::endl;
        show_usage(argv[0]);
        return 1;
    }
    
    options.query = argv[arg_index++];
    options.directory = argv[arg_index];
    
    // 目录检查 - 只检查路径是否存在，不再检查是否是目录
    if (!fs::exists(options.directory)) {
        std::cerr << "Error: Path does not exist: " << options.directory.string() << std::endl;
        return 1;
    }
    
    // 开始计时
    auto start_time = std::chrono::high_resolution_clock::now();

    // 获取系统CPU核心数
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 2;
        std::cerr << "Warning: Cannot detect hardware concurrency. Using " << num_threads << " threads." << std::endl;
    }

    std::cout << "Starting search, using " << num_threads << " worker threads." << std::endl;
    // 显示启用的选项
    if (options.ignore_case) {
        std::cout << "Option: Ignore case" << std::endl;
    }
    if (options.use_regex) {
        std::cout << "Option: Use regular expression" << std::endl;
    }

    // 创建工作线程池
    std::vector<std::thread> worker_threads;
    worker_threads.reserve(num_threads);
    for (unsigned int i = 0; i < num_threads; ++i) {
        try {
            worker_threads.emplace_back(search_file_worker, options);
        } catch (const std::system_error& e) {
            std::cerr << "Error creating thread: " << e.what() << " (" << e.code() << ")" << std::endl;
            file_queue.finish();
            for(size_t j=0; j < i; ++j) {
                 if(worker_threads[j].joinable()) worker_threads[j].join();
            }
            return 1;
        }
    }

    // 递归遍历目录并将文件加入队列
    int files_found = 0;
    try {
        if (fs::is_regular_file(options.directory)) {
            // 如果是单个文件，直接加入队列
            file_queue.push(options.directory);
            files_found = 1;
        } else if (fs::is_directory(options.directory)) {
            // 如果是目录，递归遍历
            for (const auto& entry : fs::recursive_directory_iterator(options.directory, fs::directory_options::skip_permission_denied)) {
                try {
                    if (fs::is_regular_file(entry.path())) {
                        file_queue.push(entry.path());
                        files_found++;
                    }
                } catch (const fs::filesystem_error& e) {
                    std::lock_guard<std::mutex> lock(output_mutex);
                    std::cerr << "Error accessing filesystem entry " << entry.path() << ": " << e.what() << std::endl;
                } catch (const std::exception& e) {
                    std::lock_guard<std::mutex> lock(output_mutex);
                    std::cerr << "Error processing entry " << entry.path() << ": " << e.what() << std::endl;
                }
            }
        } else {
            std::cerr << "Error: Provided path is neither a file nor a directory: " << options.directory.string() << std::endl;
            file_queue.finish();
            for (auto& t : worker_threads) { if (t.joinable()) t.join(); }
            return 1;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error during filesystem operation: " << e.what() << std::endl;
        file_queue.finish();
        for (auto& t : worker_threads) { if (t.joinable()) t.join(); }
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error during filesystem operation: " << e.what() << std::endl;
        file_queue.finish();
        for (auto& t : worker_threads) { if (t.joinable()) t.join(); }
        return 1;
    }

    // 标记所有文件已入队，等待工作线程完成
    file_queue.finish();

    for (auto& t : worker_threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // 输出统计信息
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Search completed." << std::endl;
    std::cout << "Files found: " << files_found << std::endl;
    std::cout << "Files processed: " << files_processed_count.load() << std::endl;
    std::cout << "Matches found: " << matches_found_count.load() << std::endl;
    std::cout << "Total time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}