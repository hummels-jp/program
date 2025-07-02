#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmtx;
int count = 0;

void recursive_func(int depth) {
    rmtx.lock();
    std::cout << "递归深度: " << depth << ", count: " << ++count << std::endl;
    if (depth > 0) {
        recursive_func(depth - 1); // 递归调用时可重复加锁
    }
    rmtx.unlock();
}

int main() {
    std::thread t1(recursive_func, 3);
    std::thread t2(recursive_func, 3);

    t1.join();
    t2.join();

    std::cout << "最终计数: " << count << std::endl;
    return 0;
}