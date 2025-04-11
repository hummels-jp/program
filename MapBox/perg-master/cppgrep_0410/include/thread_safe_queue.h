#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// Thread-safe queue template class
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
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    std::queue<T> queue_;
    bool is_finished_ = false;
};

#endif // THREAD_SAFE_QUEUE_H