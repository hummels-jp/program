#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex tmtx;

void work(int id) {
    for (int i = 0; i < 3; ++i) {
        if (tmtx.try_lock_for(std::chrono::milliseconds(100))) {
            std::cout << "线程 " << id << " 获得锁，工作中..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            tmtx.unlock();
        } else {
            std::cout << "线程 " << id << " 获取锁超时，放弃本次工作" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    std::thread t1(work, 1);
    std::thread t2(work, 2);

    t1.join();
    t2.join();

    std::cout << "所有线程结束" << std::endl;
    return 0;
}