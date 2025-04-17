#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic> // Include atomic type support

class ThreadPool {
public:
    // Get the singleton instance of ThreadPool
    static ThreadPool& getInstance(size_t numThreads = std::thread::hardware_concurrency());

    // Disable copy and assignment
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())>
    {
        auto task = std::make_shared<std::packaged_task<decltype(f())()>>(std::forward<F>(f));
        std::future<decltype(f())> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop.load()) { // Check atomic variable
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return result;
    }

    size_t getFreeThreadCount() const;

private:
    // Private constructor
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    std::vector<std::thread> workers; // Worker threads
    std::queue<std::packaged_task<void()>> tasks; // Task queue
    std::mutex queueMutex; // Queue mutex
    std::condition_variable condition; // Condition variable
    std::atomic_bool stop; // Atomic flag to indicate if the thread pool is stopped
    std::atomic<size_t> free_thread_count; // Idle thread count
};

#endif // THREADPOOL_H