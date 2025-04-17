#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    // 获取单例实例
    static ThreadPool& getInstance(size_t numThreads = std::thread::hardware_concurrency());

    // 禁止拷贝和赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 添加任务到线程池
    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())> {
        auto task = std::make_shared<std::packaged_task<decltype(f())()>>(std::forward<F>(f));
        std::future<decltype(f())> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop.load()) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return result;
    }

    // 获取空闲线程数量
    size_t getFreeThreadCount() const;

private:
    // 私有构造函数和析构函数
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    // 静态变量
    static ThreadPool* instance;
    static std::mutex instanceMutex;

    // 线程池相关成员
    std::vector<std::thread> workers;
    std::queue<std::packaged_task<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<size_t> free_thread_count;
};

#endif // THREADPOOL_H