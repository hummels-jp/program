#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
using namespace std;

// 线程安全队列，带容量限制
template<typename T>
class BoundedQueue {
public:
    BoundedQueue(size_t capacity) : capacity_(capacity) {}

    // 入队，阻塞直到有空位
    void push(const T& value) {
        unique_lock<mutex> lock(mtx_);
        cv_not_full_.wait(lock, [this]{ return q_.size() < capacity_; });
        q_.push(value);
        cv_not_empty_.notify_one();
    }

    // 出队，阻塞直到有元素
    void wait_and_pop(T& value) {
        unique_lock<mutex> lock(mtx_);
        cv_not_empty_.wait(lock, [this]{ return !q_.empty(); });
        value = q_.front();
        q_.pop();
        cv_not_full_.notify_one();
    }

private:
    size_t capacity_;
    queue<T> q_;
    mutex mtx_;
    condition_variable cv_not_full_;
    condition_variable cv_not_empty_;
};

BoundedQueue<int> warehouse(5);
atomic<int> global_product_id{0};

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        int product = global_product_id++;
        warehouse.push(product);
        cout << "Producer " << id << " produced: " << product << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        int item;
        warehouse.wait_and_pop(item);
        cout << "Consumer " << id << " consumed: " << item << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
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