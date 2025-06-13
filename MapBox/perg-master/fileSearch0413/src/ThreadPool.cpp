#include "ThreadPool.h"
#include <stdexcept>
#include <mutex>
#include <atomic>

// Static variable initialization
std::atomic<ThreadPool*> ThreadPool::instance{nullptr};
std::mutex ThreadPool::instanceMutex;

// Get the singleton instance (double-checked locking with atomic)
ThreadPool& ThreadPool::getInstance(size_t numThreads) {
    ThreadPool* tempInstance = instance.load(std::memory_order_acquire);
    if (!tempInstance) {
        std::lock_guard<std::mutex> lock(instanceMutex);
        tempInstance = instance.load(std::memory_order_relaxed);
        if (!tempInstance) {
            tempInstance = new ThreadPool(numThreads);
            instance.store(tempInstance, std::memory_order_release);
        }
    }
    return *tempInstance;
}

// Private constructor
ThreadPool::ThreadPool(size_t numThreads) : stop(false), free_thread_count(0) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&ThreadPool::worker, this); // Bind worker function
        ++free_thread_count;
    }
}

// Worker function (extracted from lambda)
void ThreadPool::worker() {
    while (true) {
        std::packaged_task<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // Wait until there are tasks or the pool is stopped
            condition.wait(lock, [this]() { return stop.load() || !tasks.empty(); });
            // If the pool is stopped and there are no tasks, exit the thread
            if (stop.load() && tasks.empty()) return;

            // Get the task from the queue
            task = std::move(tasks.front());
            tasks.pop();
            --free_thread_count;
        }
        // Execute the task
        task();
        ++free_thread_count;
    }
}

// Destructor
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop.store(true);
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
        worker.join();
    }
    ThreadPool* tempInstance = instance.exchange(nullptr, std::memory_order_acq_rel);
    delete tempInstance; // Free the singleton instance
}

// Get the number of free threads
size_t ThreadPool::getFreeThreadCount() const {
    return free_thread_count.load();
}