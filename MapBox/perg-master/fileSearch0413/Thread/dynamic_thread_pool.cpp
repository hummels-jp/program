#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <chrono>

class DynamicThreadPool {
public:
    DynamicThreadPool(size_t fixedThreads, size_t maxDynamicThreads, size_t queueCapacity)
        : fixedThreads(fixedThreads), maxDynamicThreads(maxDynamicThreads), queueCapacity(queueCapacity), stop(false) {
        // Create fixed threads
        for (size_t i = 0; i < fixedThreads; ++i) {
            threads.emplace_back(&DynamicThreadPool::workerThread, this, false);
        }
    }

    ~DynamicThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();

        for (std::thread& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    // Add a task to the thread pool
    bool enqueueTask(const std::function<void()>& task) {
        std::unique_lock<std::mutex> lock(queueMutex);

        // If the queue is full and dynamic threads are at max, reject the task
        if (taskQueue.size() >= queueCapacity && dynamicThreadCount >= maxDynamicThreads) {
            std::cerr << "Task rejected: queue and dynamic threads are full." << std::endl;
            return false;
        }

        // If the queue is full but dynamic threads are available, create a dynamic thread
        if (taskQueue.size() >= queueCapacity && dynamicThreadCount < maxDynamicThreads) {
            ++dynamicThreadCount;
            threads.emplace_back(&DynamicThreadPool::workerThread, this, true);
        }

        // Add the task to the queue
        taskQueue.push(task);
        condition.notify_one();
        return true;
    }

private:
    size_t fixedThreads;
    size_t maxDynamicThreads;
    size_t queueCapacity;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<size_t> dynamicThreadCount{0};

    // Worker thread function
    void workerThread(bool isDynamic) {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // Wait for a task or stop signal
                if (isDynamic) {
                    if (!condition.wait_for(lock, std::chrono::seconds(5), [this]() { return stop || !taskQueue.empty(); })) {
                        // If dynamic thread is idle for 5 seconds, exit
                        --dynamicThreadCount;
                        return;
                    }
                } else {
                    condition.wait(lock, [this]() { return stop || !taskQueue.empty(); });
                }

                if (stop && taskQueue.empty()) {
                    return;
                }

                // Get the task from the queue
                task = std::move(taskQueue.front());
                taskQueue.pop();
            }

            // Execute the task
            task();
        }
    }
};

int main() {
    DynamicThreadPool pool(5, 5, 5); // 5 fixed threads, 5 max dynamic threads, queue capacity 5

    // Enqueue tasks
    for (int i = 0; i < 20; ++i) {
        bool success = pool.enqueueTask([i]() {
            std::cout << "Task " << i << " is being processed by thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
        });

        if (!success) {
            std::cerr << "Task " << i << " was rejected." << std::endl;
        }
    }

    // Allow some time for tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(15));

    return 0;
}