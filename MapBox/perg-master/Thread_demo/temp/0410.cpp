#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool flag = false;

// 消费者线程函数
void consumer(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!flag) {
        std::cout << "消费者 " << id << " 正在等待...\n";
        cv.wait(lock);
    }
    std::cout << "消费者 " << id << " 被唤醒，开始处理任务\n";
}

// 生产者线程函数
void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟准备过程

    {
        std::lock_guard<std::mutex> lock(mtx);
        flag = true;
        std::cout << "生产者：条件已满足，通知所有消费者\n";
    }

    cv.notify_all();  // 唤醒所有等待线程
}

int main() {
    std::vector<std::thread> threads;

    // 启动多个消费者线程
    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(consumer, i);
    }

    // 启动生产者线程
    std::thread prod(producer);
    prod.join();  // 等待生产者线程结束

    
    // 等待所有线程结束
    for (auto& t : threads) {
        t.join();
    }
    

    return 0;
}
