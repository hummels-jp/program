#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void async_task(std::promise<int> prom) {
    // 模拟异步操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
    prom.set_value(42); // 设置异步操作的结果
}

int promise_demo() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future(); // 获取与 promise 关联的 future

    std::thread t(async_task, std::move(prom)); // 启动异步任务，并将 promise 传递给它

    // 在主线程中等待异步操作完成并获取结果
    std::cout << "The result is " << fut.get() << std::endl;

    t.join(); // 等待线程结束
    return 0;
}