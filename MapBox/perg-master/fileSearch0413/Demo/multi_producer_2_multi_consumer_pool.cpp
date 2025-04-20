#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t numProducers, size_t /*numConsumers*/)
        : stop(false) {
        // Start producer threads
        for (size_t i = 0; i < numProducers; ++i) {
            producers.emplace_back(&ThreadPool::producerThread, this);
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(producerMutex);
            stop = true;
        }
        producerCondition.notify_all();

        for (std::thread& producer : producers) {
            if (producer.joinable()) {
                producer.join();
            }
        }
    }

    // Add a task to the producer queue
    void enqueueTask(const std::function<void()>& task) {
        {
            std::unique_lock<std::mutex> lock(producerMutex);
            producerQueue.push(task);
        }
        producerCondition.notify_one();
    }

private:
    std::vector<std::thread> producers;
    std::queue<std::function<void()>> producerQueue;
    std::mutex producerMutex;
    std::condition_variable producerCondition;
    std::atomic<bool> stop;

    // Producer thread function
    void producerThread() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(producerMutex);
                // Wait for a task to be available or stop signal
                producerCondition.wait(lock, [this]() { return stop || !producerQueue.empty(); });

                if (stop && producerQueue.empty()) {
                    return;
                }

                // Get task from producerQueue
                task = std::move(producerQueue.front());
                producerQueue.pop();
            }

            // Execute the task
            if (task) {
                task();
            }
        }
    }
};

int main() {
    ThreadPool pool(2, 0); // 2 producers, 0 consumers

    // Enqueue tasks
    for (int i = 0; i < 10; ++i) {
        pool.enqueueTask([i]() {
            std::cout << "Task " << i << " is being produced by thread " << std::this_thread::get_id() << std::endl;
        });
    }

    // Allow some time for tasks to be produced
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}