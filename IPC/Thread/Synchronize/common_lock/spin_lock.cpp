#include <atomic>
#include <thread>
#include <iostream>

class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // busy-wait
        }
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

SpinLock spin;
int counter = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        spin.lock();
        ++counter;
        spin.unlock();
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