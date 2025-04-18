#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream> // for demonstration purposes
#include <thread>   // for std::thread      
#include <chrono>   // for std::this_thread::sleep_for

std::mutex cout_mutex; // Mutex to protect std::cout

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;

public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    void enqueue(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cond_var_.notify_one();
    }

    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this]() { return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
};

int main() {
    ThreadSafeQueue<int> queue;

    // Producer thread
    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            queue.enqueue(i);
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Produced: " << i << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        }
    });

    // Consumer thread
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int value = queue.dequeue();
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Consumed: " << value << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate work
        }
    });

    producer.join();
    consumer.join();

    return 0;
}