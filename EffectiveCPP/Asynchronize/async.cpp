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
    cout << "Main thread starts async task..." << endl;

    // 启动异步任务
    future<int> result = async(launch::async, slow_add, 3, 4);

    cout << "Main thread is free to do other work..." << endl;

    // 获取异步结果（会阻塞直到任务完成）
    int sum = result.get();
    cout << "Async result: " << sum << endl;

    return 0;
}