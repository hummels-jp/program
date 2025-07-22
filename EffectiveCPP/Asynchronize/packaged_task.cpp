#include <iostream>
#include <future>
#include <thread>
using namespace std;

// 一个耗时函数
int slow_multiply(int a, int b) {
    this_thread::sleep_for(chrono::seconds(2));
    return a * b;
}

int main() {
    // 用 packaged_task 包装函数
    packaged_task<int(int, int)> task(slow_multiply);

    // 获取 future
    future<int> result = task.get_future();

    // 启动线程执行任务
    thread t(std::move(task), 3, 5);

    cout << "Main thread is free to do other work..." << endl;

    // 获取异步结果
    int value = result.get();
    cout << "Result: " << value << endl;

    t.join();
    return 0;
}