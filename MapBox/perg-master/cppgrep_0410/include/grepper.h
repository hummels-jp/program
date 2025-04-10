#ifndef GREPPER_H
#define GREPPER_H

#include <atomic>
#include <mutex>

class Grepper {
public:
    int run(int argc, char* argv[]);

private:
    // Grepper管理的计数器
    std::atomic<int> files_found_count_{0}; // 统计找到的文件数
    std::atomic<int> files_processed_count_{0}; // 统计处理的文件数
    std::atomic<int> matches_found_count_{0}; // 统计找到的匹配数

    // 用于控制台输出（错误、结果）的互斥锁
    std::mutex output_mutex_; // 保护输出
};

#endif // GREPPER_H