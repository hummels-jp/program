#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::mutex mtx; // Mutex for synchronizing access to the queue
std::condition_variable cv; // Condition variable for signaling
std::queue<int> buffer; // Shared buffer
const unsigned int maxBufferSize = 5; // Maximum size of the buffer

// Producer function
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return buffer.size() < maxBufferSize; }); // Wait until buffer has space

        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;

        lock.unlock();
        cv.notify_all(); // Notify consumers
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate production delay
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return !buffer.empty(); }); // Wait until buffer has items

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;

        lock.unlock();
        cv.notify_all(); // Notify producers
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simulate consumption delay
    }
}

int main() {
    std::thread producer1(producer, 1);
    std::thread producer2(producer, 2);
    std::thread consumer1(consumer, 1);
    std::thread consumer2(consumer, 2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}