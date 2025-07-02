#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
#include <atomic>

// 实现一个简单的信号量类
class Semaphore {
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    unsigned int count_;

public:
    explicit Semaphore(unsigned int count = 0) : count_(count) {}

    void release() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count_;
        condition_.notify_one();
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            condition_.wait(lock);
        }
        --count_;
    }

    bool try_acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_ > 0) {
            --count_;
            return true;
        }
        return false;
    }
};

// 缓冲区大小
const int BUFFER_SIZE = 10;

// 生产者消费者模型类
class ProducerConsumer {
private:
    std::queue<int> buffer_;
    std::mutex mutex_;
    
    // 两个信号量
    Semaphore empty_slots_;   // 空槽位数量
    Semaphore filled_slots_;  // 已填充槽位数量
    
    std::atomic<bool> running_;

public:
    ProducerConsumer() : empty_slots_(BUFFER_SIZE), filled_slots_(0), running_(true) {}

    void producer(int id, int num_items) {
        for (int i = 1; i <= num_items && running_; ++i) {
            // 生产一个项目
            int item = i * 100 + id;
            
            // 等待空槽位
            empty_slots_.acquire();
            
            {
                std::lock_guard<std::mutex> lock(mutex_);
                // 将项目放入缓冲区
                buffer_.push(item);
                std::cout << "生产者 " << id << " 生产项目 " << item 
                         << ", 缓冲区大小: " << buffer_.size() << "/" << BUFFER_SIZE << std::endl;
            }
            
            // 通知消费者有新项目
            filled_slots_.release();
            
            // 模拟生产过程
            std::this_thread::sleep_for(std::chrono::milliseconds(100 + rand() % 300));
        }
        std::cout << "生产者 " << id << " 完成生产" << std::endl;
    }

    void consumer(int id, int num_items) {
        for (int i = 1; i <= num_items && running_; ++i) {
            // 等待填充槽位
            if (!filled_slots_.try_acquire()) {
                // 如果没有项目可消费，可能是程序将要退出
                if (!running_) break;
                
                filled_slots_.acquire();
                if (!running_) break;
            }
            
            int item;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (buffer_.empty()) {
                    // 这种情况不应该发生，因为信号量保护缓冲区
                    std::cerr << "错误: 消费者 " << id << " 发现空缓冲区！" << std::endl;
                    break;
                }
                
                // 从缓冲区取出项目
                item = buffer_.front();
                buffer_.pop();
                std::cout << "消费者 " << id << " 消费项目 " << item 
                         << ", 缓冲区大小: " << buffer_.size() << "/" << BUFFER_SIZE << std::endl;
            }
            
            // 通知生产者有新空槽位
            empty_slots_.release();
            
            // 模拟消费过程
            std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 500));
        }
        std::cout << "消费者 " << id << " 完成消费" << std::endl;
    }

    void stop() {
        running_ = false;
        
        // 释放所有等待的信号量，让线程可以退出
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            empty_slots_.release();
            filled_slots_.release();
        }
    }
};

int main() {
    // 设置随机数种子
    srand(static_cast<unsigned int>(time(nullptr)));
    
    ProducerConsumer pc;
    
    // 创建3个生产者线程
    std::vector<std::thread> producers;
    for (int i = 1; i <= 3; ++i) {
        producers.emplace_back(&ProducerConsumer::producer, &pc, i, 5);
    }
    
    // 创建2个消费者线程
    std::vector<std::thread> consumers;
    for (int i = 1; i <= 2; ++i) {
        consumers.emplace_back(&ProducerConsumer::consumer, &pc, i, 7);
    }
    
    // 运行一段时间后停止
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    std::cout << "主线程: 请求停止所有生产者和消费者..." << std::endl;
    pc.stop();
    
    // 等待所有线程完成
    for (auto& p : producers) {
        if (p.joinable()) p.join();
    }
    
    for (auto& c : consumers) {
        if (c.joinable()) c.join();
    }
    
    std::cout << "程序正常退出" << std::endl;
    
    return 0;
}