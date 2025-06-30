#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

// 一个耗时的计算函数
int compute_value(int param) {
    std::cout << "Computing value for param=" << param 
              << " in thread " << std::this_thread::get_id() << std::endl;
    
    // 模拟耗时操作
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    return param * 10;
}

// 另一个可以接受引用参数的异步函数
void accumulate(std::vector<int>& result, int start, int end) {
    std::cout << "Accumulating from " << start << " to " << end 
              << " in thread " << std::this_thread::get_id() << std::endl;
    
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += i;
        // 模拟耗时操作
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    result.push_back(sum);
}

int main() {
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    // 使用async启动异步任务
    auto future1 = std::async(std::launch::async, compute_value, 42);
    auto future2 = std::async(std::launch::async, compute_value, 24);
    
    // 在等待结果的同时做其他工作
    std::cout << "Main thread doing other work while waiting for results..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // 获取异步任务的结果（如果尚未完成，会等待完成）
    int result1 = future1.get();  // 阻塞直到完成
    int result2 = future2.get();  // 阻塞直到完成
    
    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    
    // 使用deferred策略（延迟执行）
    auto future3 = std::async(std::launch::deferred, compute_value, 10);
    std::cout << "Deferred task will only execute when future.get() is called" << std::endl;
    
    int result3 = future3.get();  // 此时才执行任务
    std::cout << "Result 3: " << result3 << std::endl;
    
    // 引用参数的异步任务
    std::vector<int> results;
    auto future4 = std::async(std::launch::async, accumulate, std::ref(results), 1, 5);
    
    // 等待无返回值的异步任务完成
    future4.wait();
    
    // 检查结果
    std::cout << "Accumulated result: " << results[0] << std::endl;
    
    return 0;
}