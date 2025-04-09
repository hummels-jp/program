#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

int counter = 0;             // 共享资源
std::mutex counter_mutex;    // 用于保护 counter 的互斥锁

void increment(int id) {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(counter_mutex); // 自动加锁/解锁
        ++counter;
        // sleep(1); // 模拟一些工作
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 也可以使用这个来模拟延迟
        // 可选：打印信息查看哪个线程在运行
        // std::cout << "Thread " << id << " incremented counter to " << counter << std::endl;
    }
}

int main() {
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join(); // 等待线程结束
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
// 这个程序创建了两个线程，它们同时增加一个共享变量 counter 的值。