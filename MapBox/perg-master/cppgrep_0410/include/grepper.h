#ifndef GREPPER_H
#define GREPPER_H

#include <atomic>
#include <mutex>

class Grepper {
public:
    int run(int argc, char* argv[]);

private:
    // Grepper管理的计数器
    std::atomic<int> files_found_count_{0};
    std::atomic<int> files_processed_count_{0};
    std::atomic<int> matches_found_count_{0};

    // 用于控制台输出（错误、结果）的互斥锁
    std::mutex output_mutex_;
};

#endif // GREPPER_H