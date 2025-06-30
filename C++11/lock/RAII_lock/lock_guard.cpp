#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// 共享资源
int counter = 0;
std::mutex counter_mutex;

// 使用lock_guard进行RAII方式的锁管理
void increment_counter(int id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // 创建lock_guard对象时自动加锁
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            
            // 临界区 - 访问共享资源
            ++counter;
            std::cout << "Thread " << id << " incremented counter to " 
                      << counter << std::endl;
            
            // 模拟一些工作
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            
            // 当lock_guard对象离开作用域时自动解锁
        }
        
        // 非临界区代码
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::vector<std::thread> threads;
    
    // 创建多个线程
    for (int i = 1; i <= 5; ++i) {
        threads.push_back(std::thread(increment_counter, i, 3));
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << counter << std::endl;
    
    return 0;
}