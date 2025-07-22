#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    // 入队
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        q_.push(value);
        cv_.notify_one();
    }

    // 出队，阻塞直到有元素
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]{ return !q_.empty(); });
        value = q_.front();
        q_.pop();
    }

    // 非阻塞出队
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (q_.empty()) return false;
        value = q_.front();
        q_.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return q_.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return q_.size();
    }

private:
    mutable std::mutex mtx_;
    std::queue<T> q_;
    std::condition_variable cv_;
};

const int MAX_CAPACITY = 5;
// queue<int> warehouse;
ThreadSafeQueue<int> warehouse;
mutex mtx;
condition_variable cv_producer, cv_consumer;

void producer(int id) {
    int product = 0;
    while (product < 10) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, [] { return warehouse.size() < MAX_CAPACITY; });
        warehouse.push(product);
        cout << "生产者" << id << "生产: " << product << "，当前库存: " << warehouse.size() << endl;
        ++product;
        cv_consumer.notify_one();
    }
}

void consumer(int id) {
    int consume_count = 0;
    while (consume_count < 10) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, [] { return !warehouse.empty(); });
        int item = 0;
        warehouse.wait_and_pop(item);
        cout << "消费者" << id << "消费: " << item << "，当前库存: " << warehouse.size() << endl;
        ++consume_count;
        cv_producer.notify_one();
    }
}

int main() {
    thread p1(producer, 1);
    thread p2(producer, 2);
    thread c1(consumer, 1);
    thread c2(consumer, 2);

    p1.join();
    p2.join();
    c1.join();
    c2.join();
    return 0;
}