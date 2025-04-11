#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "conditional_variable.h"
// Producer-Consumer Model

std::mutex mtx; // Mutex
std::condition_variable cv; // Condition variable
std::queue<int> buffer; // Buffer
const unsigned int MAX_BUFFER_SIZE = 5; // Buffer size
bool done = false;  // Control whether production is complete

// Producer thread function
void producer() {
    for (int i = 1; i <= 10; ++i) 
    {
        // producer thread get the lock
        std::unique_lock<std::mutex> lock(mtx);
        // producer thread will wait if the buffer is full
        // block the thread until the condition is not met
        // current thread will release the mutex and block until notified
        cv.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; }); // Wait for space

        // Produce an item
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        // Notify the consumer that an item has been produced
        // cv.notify_one(); // Notify the consumer
    }

    // Notify the consumer that production is complete
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }

    // Notify the consumer to exit if it is waiting
    cv.notify_all();
}

// Consumer thread function
void consumer() {
    // Consume items from the buffer
    while (true) {
        // consmer thread get the lock
        std::unique_lock<std::mutex> lock(mtx);
        // consumer thread will wait if the buffer is empty or production is not done
        // block the thread if the condition is not met
        // current thread will release the mutex and block until notified
        cv.wait(lock, [] { return !buffer.empty() || done; }); // 

        // If the buffer is empty and production is complete, exit
        while (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            std::cout << "  Consumed: " << item << std::endl;
        }

        if (done) break;

        cv.notify_one(); // Notify the producer to continue
    }
}

int conditional_variable_demo() {
    std::thread p1(producer);
    std::thread p2(producer);
    std::thread c1(consumer);
    std::thread c2(consumer);

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    std::cout << "All done.\n";
    return 0;
}
