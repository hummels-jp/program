#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // 自动加锁和解锁
        ++counter;
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