#include <iostream>
#include <atomic>
#include <thread>

// int counter=0;
std::atomic<int> counter(0);  // 原子整型

void increment(int times) {
    for (int i = 0; i < times; ++i) {
        counter++;  // 等价于 counter.fetch_add(1)
    }
}

int main() {
    std::thread t1(increment, 100000);
    std::thread t2(increment, 100000);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;  // 期望输出 200000
    return 0;
}
