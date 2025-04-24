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

    // Add a task to the thread pool with variadic arguments
    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using ReturnType = decltype(f(args...));

        // Create a packaged task with bound arguments
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<ReturnType> result = task->get_future();
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

    // Worker function
    void worker(); // Declaration of the worker function

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