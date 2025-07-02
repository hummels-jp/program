#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;
int value1 = 0, value2 = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        std::scoped_lock lock(mtx1, mtx2); // 同时锁定多个互斥量，防止死锁
        ++value1;
        ++value2;
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout << "value1: " << value1 << ", value2: " << value2 << std::endl;
    return 0;
}