#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <optional>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;                 // Underlying queue
    mutable std::mutex mtx;              // Mutex for synchronization
    std::condition_variable cv;          // Condition variable for signaling

public:
    // Push an element into the queue
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(value);
        cv.notify_one(); // Notify one waiting thread
    }

    // Push an element into the queue (move semantics)
    void push(T&& value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cv.notify_one(); // Notify one waiting thread
    }

    // Pop an element from the queue (blocking)
    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !queue.empty(); }); // Wait until the queue is not empty
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    // Try to pop an element from the queue (non-blocking)
    std::optional<T> tryPop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return std::nullopt; // Return empty optional if the queue is empty
        }
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    // Check if the queue is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    // Get the size of the queue
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }
};

// Example usage
void producer(ThreadSafeQueue<int>& tsQueue, int id) {
    for (int i = 0; i < 5; ++i) {
        tsQueue.push(i + id * 100);
        std::cout << "Producer " << id << " pushed: " << i + id * 100 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(ThreadSafeQueue<int>& tsQueue, int id) {
    for (int i = 0; i < 5; ++i) {
        int value = tsQueue.pop();
        std::cout << "Consumer " << id << " popped: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    ThreadSafeQueue<int> tsQueue;

    std::thread producer1(producer, std::ref(tsQueue), 1);
    std::thread producer2(producer, std::ref(tsQueue), 2);
    std::thread consumer1(consumer, std::ref(tsQueue), 1);
    std::thread consumer2(consumer, std::ref(tsQueue), 2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}