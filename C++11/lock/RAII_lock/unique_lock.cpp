#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

// 共享资源
int counter = 0;
std::mutex counter_mutex;
std::condition_variable cv;
bool ready = false;

// 使用unique_lock进行更灵活的锁管理
void worker(int id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 创建unique_lock对象
        std::unique_lock<std::mutex> lock(counter_mutex);
        
        // 等待条件变量
        cv.wait(lock, [] { return ready; });
        
        // 临界区 - 访问共享资源
        ++counter;
        std::cout << "Thread " << id << " incremented counter to " 
                  << counter << std::endl;
        
        // 可以提前解锁（这是unique_lock的特性，lock_guard不支持）
        lock.unlock();
        std::cout << "Thread " << id << " released the lock early" << std::endl;
        
        // 做一些不需要锁的工作
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
        // 可以重新加锁（lock_guard不支持）
        lock.lock();
        std::cout << "Thread " << id << " re-acquired the lock" << std::endl;
        
        // 离开作用域时自动解锁（除非之前已经手动解锁）
    }
}

// 主线程通知工作线程继续
void notifier() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(counter_mutex);
        ready = true;
    }
    // 唤醒所有等待的线程
    std::cout << "Notifying all workers to proceed..." << std::endl;
    cv.notify_all();
}

int main() {
    std::vector<std::thread> threads;
    
    // 创建通知线程
    std::thread notify_thread(notifier);
    
    // 创建多个工作线程
    for (int i = 1; i <= 3; ++i) {
        threads.push_back(std::thread(worker, i, 2));
    }
    
    // 等待所有线程完成
    notify_thread.join();
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << counter << std::endl;
    
    return 0;
}