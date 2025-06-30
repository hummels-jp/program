#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

// 共享队列，用于线程间通信
std::queue<int> data_queue;
std::mutex queue_mutex;
std::condition_variable cv;
bool finished = false;

// 生产者线程：生成数据并通知消费者
void producer() {
    for (int i = 1; i <= 10; ++i) {
        // 模拟一些工作
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // 添加数据到队列
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            data_queue.push(i);
            std::cout << "Producer: " << i << " added to queue" << std::endl;
        }
        
        // 通知一个等待的消费者
        cv.notify_one();
    }
    
    // 通知已完成生产
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        finished = true;
    }
    
    // 通知所有等待的消费者
    cv.notify_all();
    std::cout << "Producer finished" << std::endl;
}

// 消费者线程：等待并处理数据
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        
        // 等待队列不为空或生产完成
        cv.wait(lock, [] { 
            return !data_queue.empty() || finished; 
        });
        
        // 检查是否完成且队列为空
        if (finished && data_queue.empty()) {
            std::cout << "Consumer " << id << ": no more items, exiting" << std::endl;
            break;
        }
        
        // 处理队列中的数据
        int value = data_queue.front();
        data_queue.pop();
        
        std::cout << "Consumer " << id << ": processed value " << value << std::endl;
        
        // 在处理下一项前释放锁
        lock.unlock();
        
        // 模拟处理数据
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    // 启动一个生产者和两个消费者
    std::thread producer_thread(producer);
    std::thread consumer1(consumer, 1);
    std::thread consumer2(consumer, 2);
    
    // 等待所有线程完成
    producer_thread.join();
    consumer1.join();
    consumer2.join();
    
    std::cout << "All threads completed" << std::endl;
    
    return 0;
}