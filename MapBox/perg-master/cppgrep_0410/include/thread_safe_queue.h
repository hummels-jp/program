#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// Thread-safe queue template class using condition variables
// This class provides a thread-safe queue implementation with push, try_pop, and finish methods    
// It uses a mutex for synchronization and a condition variable to notify waiting threads
// The queue can be used to safely pass data between threads
template<typename T>
class ThreadSafeQueue {
public:
    // Push an element into the queue
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_.notify_one();
    }

    // Try to pop an element from the queue
    // Returns true if the queue is empty but not finished; also returns true if an element is successfully retrieved
    bool try_pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        // Wait until the queue is not empty or finished
        // if the queue is empty or not finished, release the lock and wait
        cond_.wait(lock, [this] {
            return !queue_.empty() || is_finished_;
        });

        // If the queue is empty and finished, return false
        if (queue_.empty()) {
            return !is_finished_;
        }

        // Retrieve the first element in the queue
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // Mark the queue as finished
    void finish() {
        std::lock_guard<std::mutex> lock(mutex_);
        is_finished_ = true;
        cond_.notify_all();
    }

    // Check if the queue is finished
    bool is_finished() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return is_finished_;
    }

private:
    mutable std::mutex mutex_; // Mutex for thread safety
    std::condition_variable cond_; // Condition variable for synchronization
    std::queue<T> queue_; // Underlying queue
    bool is_finished_ = false; // Flag to indicate if the queue is finished
};

#endif // THREAD_SAFE_QUEUE_H