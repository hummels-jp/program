#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// 共享资源
int counter = 0;
std::mutex counter_mutex;  // 保护counter的互斥锁

void increment_counter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 加锁，保护临界区
        counter_mutex.lock();
        
        // 临界区 - 访问共享资源
        ++counter;
        std::cout << "Thread " << std::this_thread::get_id() 
                  << " incremented counter to: " << counter << std::endl;
        
        // 解锁，释放互斥锁
        counter_mutex.unlock();
        
        // 非临界区代码 - 不需要保护
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// 使用RAII方式管理锁
void safe_increment(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 使用lock_guard自动管理锁的获取和释放
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            ++counter;
            std::cout << "Thread " << std::this_thread::get_id() 
                      << " safely incremented counter to: " << counter << std::endl;
        }
        
        // lock_guard在花括号结束时自动释放锁
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::vector<std::thread> threads;
    
    // 创建多个线程
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(safe_increment, 3));
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << counter << std::endl;
    
    return 0;
}