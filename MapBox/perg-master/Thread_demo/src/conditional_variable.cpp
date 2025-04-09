#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "conditional_variable.h"

static std::mutex mtx; // Mutex for protecting shared data
std::condition_variable cv; // Condition variable for synchronization
std::queue<int> dataQueue; // Queue to hold produced data
bool done = false; // Flag to indicate when the producer is done

// This program demonstrates the use of std::condition_variable to synchronize producer and consumer threads.
void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
        dataQueue.push(i); // Produce data and push it to the queue
        std::cout << "Produced: " << i << std::endl;
        // cv.notify_one(); // Notify one waiting consumer thread
    }

    std::unique_lock<std::mutex> lock(mtx);
    done = true; // Set the done flag to true
    // cv.notify_all(); // Notify all waiting consumer threads

}

// Function to consume data from the queue
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
        // Wait until there is data in the queue or the producer is done
        // The lambda function checks if the queue is empty and if the producer is done
        // cv.wait(lock); // Wait for notification 等待通知，释放锁
        cv.wait(lock, [] { return !dataQueue.empty() || done; }); // 条件变量，必须等到通知，同时满足条件，才能被唤醒

        while (!dataQueue.empty()) {
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }

        // If the producer is done and the queue is empty, exit the loop
        // This check is necessary to avoid a spurious wakeup
        if (done && dataQueue.empty()) {
            break;
        }
    }
}

int conditional_variable_demo() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    done = true; // Set the done flag to true
    cv.notify_all(); // Notify all waiting consumer threads
    consumerThread.join();

    return 0;
}