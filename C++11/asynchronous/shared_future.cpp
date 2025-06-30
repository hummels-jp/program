#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

// 执行计算的函数
int calculate_result(int input) {
    std::cout << "Calculating result for input " << input 
              << " in thread " << std::this_thread::get_id() << std::endl;
    
    // 模拟耗时计算
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    return input * input;
}

// 使用共享future的工作函数
void worker(std::shared_future<int> shared_future, int worker_id) {
    std::cout << "Worker " << worker_id << " waiting for result in thread " 
              << std::this_thread::get_id() << std::endl;
    
    try {
        // 等待并获取结果（多个线程可以同时调用）
        int result = shared_future.get();
        std::cout << "Worker " << worker_id << " got result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Worker " << worker_id << " caught exception: " 
                  << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    // 创建一个future
    std::future<int> future = std::async(std::launch::async, calculate_result, 42);
    
    // 将future转换为shared_future（可以被多个线程共享）
    std::shared_future<int> shared_future = future.share();
    
    // 创建多个线程，每个线程都访问同一个shared_future
    std::vector<std::thread> threads;
    for (int i = 1; i <= 3; ++i) {
        threads.push_back(std::thread(worker, shared_future, i));
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    // 演示异常情况
    std::promise<int> promise;
    std::shared_future<int> error_future = promise.get_future().share();
    
    // 设置异常
    promise.set_exception(std::make_exception_ptr(std::runtime_error("Simulated error")));
    
    // 创建工作线程处理异常情况
    std::vector<std::thread> error_threads;
    for (int i = 4; i <= 5; ++i) {
        error_threads.push_back(std::thread(worker, error_future, i));
    }
    
    // 等待异常处理线程
    for (auto& t : error_threads) {
        t.join();
    }
    
    std::cout << "All workers completed" << std::endl;
    
    return 0;
}