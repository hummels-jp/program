
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>

// 工作线程函数，使用promise设置结果
void worker(std::promise<std::string> promise, int value) {
    try {
        std::cout << "Worker thread started with value: " << value << std::endl;
        
        // 模拟耗时任务
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        if (value < 0) {
            throw std::runtime_error("Negative value not allowed");
        }
        
        // 计算并设置结果
        std::string result = "Result: " + std::to_string(value * value);
        
        // 将计算完成的结果放入promise
        promise.set_value(result);
    }
    catch (...) {
        // 出现异常时，将异常传递给future
        promise.set_exception(std::current_exception());
    }
}

int main() {
    // 创建promise
    std::promise<std::string> promise;
    
    // 从promise获取future
    std::future<std::string> future = promise.get_future();
    
    // 在新线程中启动worker，并传递promise
    std::thread t(worker, std::move(promise), 42);
    
    std::cout << "Main thread waiting for result..." << std::endl;
    
    try {
        // 等待并获取结果
        std::string result = future.get();
        std::cout << "Got result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception from worker thread: " << e.what() << std::endl;
    }
    
    // 等待线程结束
    t.join();
    
    // 演示带异常的情况
    std::promise<std::string> promise2;
    std::future<std::string> future2 = promise2.get_future();
    
    std::thread t2(worker, std::move(promise2), -5);
    
    try {
        std::string result = future2.get();
        std::cout << "Got result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception from worker thread: " << e.what() << std::endl;
    }
    
    t2.join();
    
    return 0;
}