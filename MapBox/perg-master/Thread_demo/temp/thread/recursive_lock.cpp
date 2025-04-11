#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmtx;

void recursiveFunction(int count) {
    if (count <= 0) return;

    rmtx.lock();
    std::cout << "Lock acquired at level: " << count << std::endl;

    recursiveFunction(count - 1);  // 递归调用，仍然加锁

    std::cout << "Unlocking level: " << count << std::endl;
    rmtx.unlock();
}

int main() {
    std::thread t1(recursiveFunction, 3);
    t1.join();
    return 0;
}
