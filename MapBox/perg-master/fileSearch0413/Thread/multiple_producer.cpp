#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <chrono>

// 线程安全队列
template<typename T>
class SafeQueue {
public:
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push(value);
        cv_.notify_one();
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        if (queue_.empty()) return std::nullopt;
        T value = queue_.front();
        queue_.pop();
        return value;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mtx_);
        return queue_.empty();
    }

    void swap(SafeQueue<T>& other) {
        std::unique_lock<std::mutex> lock1(mtx_, std::defer_lock);
        std::unique_lock<std::mutex> lock2(other.mtx_, std::defer_lock);
        std::lock(lock1, lock2);
        queue_.swap(other.queue_);
    }

private:
    std::queue<T> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

// 生产者线程函数
void producer(SafeQueue<int>& producer_queue, int id, int count) {
    for (int i = 0; i < count; ++i) {
        int msg = id * 100 + i;
        producer_queue.push(msg);
        std::cout << "Producer " << id << " produced: " << msg << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// 消费者线程函数
void consumer(SafeQueue<int>& consumer_queue, SafeQueue<int>& producer_queue, int id, int total_produce) {
    int consumed = 0;
    while (consumed < total_produce) {
        auto val = consumer_queue.pop();
        if (val.has_value()) {
            std::cout << "Consumer " << id << " consumed: " << *val << std::endl;
            ++consumed;
        } else {
            // 消费者队列为空，交换队列
            consumer_queue.swap(producer_queue);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

int main() {
    SafeQueue<int> producer_queue;
    SafeQueue<int> consumer_queue;

    const int producer_count = 3;
    const int consumer_count = 2;
    const int produce_per_producer = 5;
    const int total_produce = producer_count * produce_per_producer / consumer_count;

    // 启动生产者线程
    std::vector<std::thread> producers;
    for (int i = 0; i < producer_count; ++i) {
        producers.emplace_back(producer, std::ref(producer_queue), i, produce_per_producer);
    }

    // 启动消费者线程
    std::vector<std::thread> consumers;
    for (int i = 0; i < consumer_count; ++i) {
        consumers.emplace_back(consumer, std::ref(consumer_queue), std::ref(producer_queue), i, total_produce);
    }

    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();

    std::cout << "All done." << std::endl;
    return 0;
}