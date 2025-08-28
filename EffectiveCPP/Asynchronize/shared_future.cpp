#include <iostream>
#include <future>
#include <thread>
using namespace std;

// 一个耗时函数
int slow_add(int a, int b) {
    this_thread::sleep_for(chrono::seconds(2));
    return a + b;
}

int main() {
    // 启动异步任务，返回 future
    future<int> fut = async(launch::async, slow_add, 3, 4);

    // 将 future 转为 shared_future，可以被多个线程安全共享
    shared_future<int> sfut = fut.share();

    // 多个线程都可以获取同一个结果
    thread t1([sfut]() {
        cout << "Thread 1 result: " << sfut.get() << endl;
    });
    thread t2([sfut]() {
        cout << "Thread 2 result: " << sfut.get() << endl;
    });

    t1.join();
    t2.join();
    return 0;
}