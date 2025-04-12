#include <iostream>
#include <thread>
#include <future>

// 一个用于演示的函数，它将在另一个线程中执行
void calculateSum(std::promise<int> promiseObj, int a, int b) {
    // 模拟一些计算
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int result = a + b;
    // 将结果设置到 promise 中
    promiseObj.set_value(result);
}

int main() {
    // 创建一个 std::promise 对象
    std::promise<int> promiseObj;

    // 获取与 promise 关联的 future 对象
    std::future<int> futureObj = promiseObj.get_future();

    // 创建一个线程并传递 promise 对象
    std::thread workerThread(calculateSum, std::move(promiseObj), 10, 20);

    // 在主线程中等待结果
    std::cout << "等待线程完成计算..." << std::endl;
    int result = futureObj.get(); // 阻塞直到线程计算完成

    std::cout << "计算结果是: " << result << std::endl;

    // 等待子线程完成
    if (workerThread.joinable()) {
        workerThread.join();
    }

    return 0;
}