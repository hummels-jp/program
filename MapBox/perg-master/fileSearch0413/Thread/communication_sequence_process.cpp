#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <chrono>

// CSP风格的通道，支持容量限制
template<typename T>
class Channel {
public:
    explicit Channel(size_t capacity = 16) : capacity_(capacity) {}

    void send(const T& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        // 如果队列已满，等待直到有空间
        cv_full_.wait(lock, [this] { return queue_.size() < capacity_ || closed_; });
        if (closed_) return;

        // 如果队列已满，等待直到有空间
        queue_.push(value);
        cv_empty_.notify_one();
    }

    // receive会阻塞直到有数据
    std::optional<T> receive() {
        // 如果队列为空，等待直到有数据
        std::unique_lock<std::mutex> lock(mtx_);
        cv_empty_.wait(lock, [this] { return !queue_.empty() || closed_; });
        if (!queue_.empty()) {
            T value = queue_.front();
            queue_.pop();
            cv_full_.notify_one();
            return value;
        }
        return std::nullopt;
    }

    void close() {
        {
            std::unique_lock<std::mutex> lock(mtx_);
            closed_ = true;
        }
        cv_empty_.notify_all();
        cv_full_.notify_all();
    }

private:
    std::queue<T> queue_;
    size_t capacity_;
    std::mutex mtx_;
    std::condition_variable cv_empty_;
    std::condition_variable cv_full_;
    bool closed_ = false;
};

// 生产者
void producer(Channel<int>& ch, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Produce: " << i << std::endl;
        ch.send(i);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ch.close();
}

// 消费者
void consumer(Channel<int>& ch) {
    while (true) {
        auto val = ch.receive();
        if (!val.has_value()) break;
        std::cout << "Consume: " << *val << std::endl;
    }
}

int main() {
    Channel<int> ch(4); // 设置容量为4
    std::thread prod(producer, std::ref(ch), 10);
    std::thread cons(consumer, std::ref(ch));
    prod.join();
    cons.join();
    return 0;
}