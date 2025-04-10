#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// 线程安全队列模板类
template<typename T>
class ThreadSafeQueue {
public:
    // 将元素推入队列
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_.notify_one();
    }

    // 尝试从队列弹出元素
    // 如果队列为空但未结束，返回true；如果成功获取元素，也返回true
    bool try_pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        // 等待直到队列非空或已结束
        cond_.wait(lock, [this] {
            return !queue_.empty() || is_finished_;
        });

        // 如果队列为空且已结束，返回false
        if (queue_.empty()) {
            return !is_finished_;
        }

        // 获取队列首个元素
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // 标记队列已完成
    void finish() {
        std::lock_guard<std::mutex> lock(mutex_);
        is_finished_ = true;
        cond_.notify_all();
    }

    // 检查队列是否已完成
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