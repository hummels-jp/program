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
    // Get the singleton instance
    static ThreadPool& getInstance(size_t numThreads = std::thread::hardware_concurrency());

    // Disable copy and assignment
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Add a task to the thread pool
    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())> {
        // Check if the task is callable
        // decltype(f())()> is used to deduce the return type of the function
        // std::forward<F>(f) is used to perfectly forward the function
        // to preserve its value category (lvalue/rvalue)
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

    // Get the number of free threads
    size_t getFreeThreadCount() const;

private:
    // Private constructor and destructor
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    // Static variables
    static std::atomic<ThreadPool*> instance; // Use atomic for thread safety
    static std::mutex instanceMutex;

    // Thread pool members
    std::vector<std::thread> workers;
    std::queue<std::packaged_task<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<size_t> free_thread_count;
};

#endif // THREADPOOL_H