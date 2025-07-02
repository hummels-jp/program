#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::recursive_timed_mutex rtm;

void recursive_func(int id, int depth) {
    if (rtm.try_lock_for(std::chrono::milliseconds(100))) {
        std::cout << "线程 " << id << " 获得锁，递归深度: " << depth << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (depth > 0) {
            recursive_func(id, depth - 1); // 递归调用，可重复加锁
        }
        rtm.unlock();
    } else {
        std::cout << "线程 " << id << " 获取锁超时，递归深度: " << depth << std::endl;
    }
}

int main() {
    std::thread t1(recursive_func, 1, 3);
    std::thread t2(recursive_func, 2, 3);

    t1.join();
    t2.join();

    std::cout << "所有线程结束" << std::endl;
    return 0;
}