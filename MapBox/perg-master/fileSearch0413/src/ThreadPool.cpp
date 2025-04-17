#include "ThreadPool.h"
#include <stdexcept>

// Get the singleton instance of ThreadPool
// hungry singleton pattern
// This pattern ensures that the instance is created when it is first accessed, and it is thread-safe.
ThreadPool& ThreadPool::getInstance(size_t numThreads) {
    static ThreadPool instance(numThreads);
    return instance;
}

// Private constructor
ThreadPool::ThreadPool(size_t numThreads) : stop(false), free_thread_count(0) {
    for (size_t i = 0; i < numThreads; ++i) 
    {
        workers.emplace_back([this]() {
            while (true) {
                std::packaged_task<void()> task;
                {
                    // get the task from the queue and 
                    std::unique_lock<std::mutex> lock(queueMutex);
                    // Wait until there is a task or the pool is stopped
                    condition.wait(lock, [this]() { return stop.load() || !tasks.empty(); });
                    // If the pool is stopped and there are no tasks, exit the thread
                    if (stop.load() && tasks.empty()) return;
                    // If there are tasks, get the next task
                    task = std::move(tasks.front());
                    tasks.pop();
                    --free_thread_count; // Decrease idle thread count
                }
                task();
                ++free_thread_count; // Increase idle thread count
            }
        });
        ++free_thread_count; // All threads are idle at initialization
    }
}

// Destructor
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop.store(true); // Set atomic variable to true
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
        worker.join();
    }
}

// Get the count of free threads
size_t ThreadPool::getFreeThreadCount() const {
    return free_thread_count.load();
}