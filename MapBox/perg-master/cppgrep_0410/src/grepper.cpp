#include "grepper.h"
#include "argument_parser.h"
#include "directory_walker.h"
#include "file_searcher.h"
#include "thread_safe_queue.h"
#include "result.h"
#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <optional> // For optional<SearchOptions>


int Grepper::run(int argc, char* argv[]) {
    ArgumentParser parser;
    std::optional<SearchOptions> optionsOpt = parser.parse(argc, argv);

    if (!optionsOpt) {
        return 1; // 解析器处理的错误或帮助请求
    }
    SearchOptions options = *optionsOpt; // 从optional中获取选项

    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "开始搜索，使用 " << options.num_threads << " 个工作线程。" << std::endl;
    if (options.ignore_case) std::cout << "选项：忽略大小写" << std::endl;
    if (options.use_regex) std::cout << "选项：使用正则表达式" << std::endl;

    ThreadSafeQueue<fs::path> fileQueue; // 线程安全的文件队列
    ThreadSafeQueue<Result> resultQueue; // 线程安全的结果队列

    // --- 启动线程 ---
    std::vector<std::thread> workerThreads;
    workerThreads.reserve(options.num_threads);

    // 遍历器（生产者）线程
    DirectoryWalker walker(options.directory, fileQueue, files_found_count_, output_mutex_);
    if (!walker.isValid()) return 1; // 如果初始路径检查失败则退出
    std::thread walkerThread(&DirectoryWalker::run, &walker);

    // 搜索器（消费者）线程
    for (unsigned int i = 0; i < options.num_threads; ++i) {
         // 每个搜索器获取队列、计数器、选项、互斥锁的引用
         workerThreads.emplace_back(FileSearcher{options, fileQueue, resultQueue,
                                   files_processed_count_, matches_found_count_, output_mutex_});
    }

    // --- 处理结果（在主线程中）并等待 ---
    // 等待遍历器完成添加文件
    walkerThread.join();
    // 遍历器在完成时调用fileQueue.finish()

    // 等待搜索器完成处理
    for (auto& t : workerThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    // 标记不会再产生更多结果
    resultQueue.finish();

    // 处理并打印结果队列中的结果
    Result foundResult;
    while (resultQueue.try_pop(foundResult)) {
         if (foundResult.file_path.empty()) continue; // 处理可能的空结果
         std::cout << foundResult.file_path.string() << ":"
                   << foundResult.line_number << ":"
                   << foundResult.line_content << std::endl;
    }

    // --- 输出统计信息 ---
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "搜索完成。" << std::endl;
    std::cout << "遍历器找到的文件数：" << files_found_count_.load() << std::endl;
    std::cout << "搜索器处理的文件数：" << files_processed_count_.load() << std::endl;
    std::cout << "找到的匹配数：" << matches_found_count_.load() << std::endl;
    std::cout << "总耗时：" << duration.count() << " 毫秒" << std::endl;

    return 0;
}