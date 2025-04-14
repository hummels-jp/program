#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic> // 引入原子类型支持

class ThreadPool {
public:
    // 获取 ThreadPool 单例实例
    static ThreadPool& getInstance(size_t numThreads = std::thread::hardware_concurrency()) {
        static ThreadPool instance(numThreads);
        return instance;
    }

    // 禁止拷贝和赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())> {
        auto task = std::make_shared<std::packaged_task<decltype(f())()>>(std::forward<F>(f));
        std::future<decltype(f())> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop.load()) { // 检查原子变量
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return result;
    }

    size_t getFreeThreadCount() const {
        return free_thread_count.load();
    }

private:
    // 私有构造函数
    ThreadPool(size_t numThreads) : stop(false), free_thread_count(0) {
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
                        --free_thread_count; // 减少闲置线程计数
                    }
                    task();
                    ++free_thread_count; // 增加闲置线程计数
                }
            });
            ++free_thread_count; // 初始化时所有线程都为空闲状态
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop.store(true); // 设置原子变量为 true
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    std::vector<std::thread> workers; // 工作线程
    std::queue<std::packaged_task<void()>> tasks; // 任务队列
    std::mutex queueMutex; // 队列互斥锁
    std::condition_variable condition; // 条件变量
    std::atomic_bool stop; // 使用原子类型的停止标志
    std::atomic<size_t> free_thread_count; // 闲置线程计数
};

#endif // THREADPOOL_H