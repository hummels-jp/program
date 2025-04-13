#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::packaged_task<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())> {
        // Return a future to the result of the task
        // This allows the task to be run asynchronously
        // and the result to be retrieved later
        // ecltype (f()) is the return type of the function
        // std::forward<F>(f) is used to perfectly forward the function
        auto task = std::make_shared<std::packaged_task<decltype(f())()>>(std::forward<F>(f));
        // std::packaged_task is a wrapper for a callable object
        // std::future<decltype(f())> is the future object that will hold the result
        // std::shared_ptr is used to share ownership of the task
        // std::promise is used to set the value of the future
        std::future<decltype(f())> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // Don't allow enqueueing after stopping the pool
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // Add the task to the queue
            // std::packaged_task<void()> is a wrapper for a callable object
            // std::function<void()> is a function that takes no arguments and returns void
            // std::function is used to store the task
            // std::queue is used to store the tasks
            // std::mutex is used to protect the queue
            // std::condition_variable is used to notify the worker threads
            // std::unique_lock is used to lock the mutex
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return result;
    }

private:
    std::vector<std::thread> workers; // Vector of worker threads
    std::queue<std::packaged_task<void()>> tasks; // Queue of tasks
    std::mutex queueMutex; // Mutex to protect the queue
    std::condition_variable condition; // Condition variable to notify the worker threads
    bool stop = false; //  Flag to indicate if the pool is stopped
    // std::condition_variable is used to notify the worker threads
    // std::mutex is used to protect the queue
    // std::unique_lock is used to lock the mutex
    // std::packaged_task is a wrapper for a callable object
    // std::function is used to store the task
    // std::queue is used to store the tasks
    // std::thread is used to create the worker threads
    // std::vector is used to store the worker threads
    // std::future is used to retrieve the result of the task
    // std::promise is used to set the value of the future

};

#endif // THREADPOOL_H