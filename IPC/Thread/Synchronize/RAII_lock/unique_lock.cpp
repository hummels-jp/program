#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        std::unique_lock<std::mutex> lock(mtx); // 自动加锁
        ++counter;
        // lock.unlock(); // 你可以随时手动解锁
        // lock.lock();   // 也可以随时手动加锁
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout << "最终计数器值: " << counter << std::endl;
    return 0;
}