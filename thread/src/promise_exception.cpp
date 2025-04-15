#include <iostream>
#include <thread>
#include <future>
#include <exception>

// 子线程函数
void threadFunction(std::promise<int> promiseObj) {
    try {

        // 如果没有异常，设置返回值
        promiseObj.set_value(42);

        // 模拟抛出异常
        throw std::runtime_error("An error occurred in the sub thread");
    } catch (...) {
        // 捕获所有异常并将其传递给 promise
        promiseObj.set_exception(std::current_exception());
    }
}

int main() {
    // 创建 promise 和 future 对象
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();

    // 启动线程
    std::thread t(threadFunction, std::move(promiseObj));

    try {
        // 从 future 获取结果或异常
        int result = futureObj.get(); // 如果子线程抛出了异常，这里会重新抛出
        std::cout << "Result from thread: " << result << std::endl;
    } catch (const std::exception& ex) {
        // 捕获并处理子线程中的异常
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }

    // 等待线程结束
    t.join();
    return 0;
}