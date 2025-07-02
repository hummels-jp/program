#include <iostream>
#include <future>
#include <thread>
#include <chrono>

void longRunningTask() {
    std::cout << "Task started in thread: " << std::this_thread::get_id() << std::endl;
    
    // 模拟耗时操作
    for (int i = 1; i <= 5; ++i) {
        std::cout << "Task working... " << i << "/5" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    std::cout << "Task completed!" << std::endl;
}

void demoWithoutCapture() {
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    std::cout << "\n--- Demo: future not captured ---" << std::endl;
    std::cout << "Creating async task..." << std::endl;
    
    // async返回的future没有被捕获，会在语句结束时析构
    // 这会导致主线程在这里阻塞，直到longRunningTask完成
    std::async(std::launch::async, longRunningTask);
    
    std::cout << "Statement completed - but had to wait for task!" << std::endl;
}

void demoWithCapture() {
    std::cout << "\n--- Demo: future captured ---" << std::endl;
    std::cout << "Creating async task with captured future..." << std::endl;
    
    // 捕获返回的future， 没有阻塞主线程
    // auto future = std::async(std::launch::async, longRunningTask);

    // 捕获返回的future， 会阻塞主线程直到任务完成
    {
        auto future = std::async(std::launch::async, longRunningTask);
    }
    
    
    
    std::cout << "Future is now captured, execution continues immediately" << std::endl;
    std::cout << "Doing other work in main thread..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Now explicitly waiting for task completion..." << std::endl;
    // 显式等待任务完成
    // future.wait();
    // std::cout << "Task is now definitely complete" << std::endl;
}

void demoWithDeferred() {
    std::cout << "\n--- Demo: deferred execution ---" << std::endl;
    
    // 使用deferred策略，不会立即启动新线程
    auto future = std::async(std::launch::deferred, longRunningTask);
    
    std::cout << "Created deferred task - it hasn't started yet" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Calling get() will start the task in current thread" << std::endl;
    future.get(); // 此时才会执行任务，在当前线程中
}

int main() {
    std::cout << "=== std::async future destruction behavior demo ===" << std::endl;
    
    // demoWithoutCapture();
    demoWithCapture();
    // demoWithDeferred();
    
    std::cout << "\n=== All demonstrations complete ===" << std::endl;
    return 0;
}