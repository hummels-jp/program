#include <iostream>
#include <thread>
#include <future>
using namespace std;

// 子线程任务，设置 promise 的值
void worker(promise<int> prom) {
    this_thread::sleep_for(chrono::seconds(2));
    prom.set_value(42); // 设置结果
}

int main() {
    promise<int> prom;
    future<int> fut = prom.get_future();

    thread t(worker, std::move(prom));

    cout << "Main thread is waiting for result..." << endl;
    int result = fut.get(); // 阻塞直到子线程设置值
    cout << "Result from worker: " << result << endl;

    t.join();
    return 0;
}