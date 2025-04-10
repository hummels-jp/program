// thread_pool.cpp
#include "thread_pool.h"

// thread_pool.h constructor and destructor 
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    // Create and launch a number of worker threads
    workers.reserve(numThreads); // Reserve space for threads
    for (size_t i = 0; i < numThreads; ++i) 
    {
        // Create a thread that will run the worker function
        workers.emplace_back([this]  
        {
            while (true) {
                // Wait for a task to be available
                std::function<void()> task; 
                {
                    // Lock the queue and wait for a task
                    std::unique_lock<std::mutex> lock(queueMutex);
                    // Wait until there is a task or stop is true
                    // The condition variable will notify when a task is available
                    // or when the thread pool is stopping
                    // The lambda function checks if the thread pool is stopping or if there are tasks
                    // If stop is true and there are no tasks, exit the loop
                    // If there are tasks, get the task from the queue
                    // The task is a std::function<void()>, so it can be any callable
                    // that takes no arguments and returns void
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}
