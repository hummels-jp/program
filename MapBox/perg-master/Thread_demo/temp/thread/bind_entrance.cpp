#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
using namespace std;

mutex g_mtx;

void doWork(int a, int b) {
    unique_lock<mutex> lock(g_mtx);
    std::cout << "Sum: " << a + b << std::endl;
}

int main() {
    auto boundFunc = std::bind(doWork, 3, 4); // 绑定参数
    std::thread t(boundFunc); // 作为线程入口

    auto boundFunc1 = std::bind(doWork, std::placeholders::_1, 4);
    std::thread t2(boundFunc1, 5);
    t.join();
    t2.join();
    return 0;
}
