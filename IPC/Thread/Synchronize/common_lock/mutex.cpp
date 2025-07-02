#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        mtx.lock();         // 加锁，进入临界区
        ++counter;          // 临界区：对共享资源操作
        mtx.unlock();       // 解锁，离开临界区
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