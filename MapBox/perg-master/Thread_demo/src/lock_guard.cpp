#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

#include "lock_guard.h"

std::mutex mtx; // 全局互斥锁
int shared_resource = 0;

void incrementResource(int id) {
    std::lock_guard<std::mutex> lock(mtx); // 自动管理锁的生命周期
    std::cout << "Thread " << id << " is incrementing the resource.\n";
    ++shared_resource;
    std::cout << "Thread " << id << " updated resource to " << shared_resource << ".\n";
}

int lock_guard_demo() {
    std::thread t1(incrementResource, 1);
    std::thread t2(incrementResource, 2);

    t1.join();
    t2.join();

    std::cout << "Final value of shared resource: " << shared_resource << std::endl;

    return 0;
}