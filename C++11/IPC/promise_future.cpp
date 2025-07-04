#include <iostream>
#include <thread>
#include <future>
using namespace std;

// 子线程函数，接收 promise
void worker(promise<int> prom) {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "worker done" << endl;
    prom.set_value(42); // 设置返回值
}

int main() {
    promise<int> prom;
    future<int> fut = prom.get_future(); // 获取 future

    // 启动子线程
    thread t(worker, std::move(prom));

    // 等待并获取子线程返回值
    int result = fut.get();
    cout << "sub thread return " << result << endl;

    t.join();
    return 0;