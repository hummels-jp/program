#include "ThreadPool.h"
#include <stdexcept>
#include <mutex>
#include <atomic>

// 静态变量初始化
ThreadPool* ThreadPool::instance = nullptr;
std::mutex ThreadPool::instanceMutex;

// 获取单例实例（双重检查锁实现）
ThreadPool& ThreadPool::getInstance(size_t numThreads) {
    if (!instance) {
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (!instance) {
            instance = new ThreadPool(numThreads);
        }
    }
    return *instance;
}

// 私有构造函数
ThreadPool::ThreadPool(size_t numThreads) : stop(false), free_thread_count(0) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::packaged_task<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this]() { return stop.load() || !tasks.empty(); });
                    if (stop.load() && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                    --free_thread_count;
                }
                task();
                ++free_thread_count;
            }
        });
        ++free_thread_count;
    }
}

// 析构函数
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop.store(true);
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
        worker.join();
    }
    delete instance; // 释放单例实例
    instance = nullptr;
}

// 获取空闲线程数量
size_t ThreadPool::getFreeThreadCount() const {
    return free_thread_count.load();
}