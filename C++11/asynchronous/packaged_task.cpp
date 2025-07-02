#include <iostream>
#include <future>
#include <thread>
#include <functional>
#include <vector>
#include <string>

// 用于演示的计算函数
int compute_sum(const std::vector<int>& data) {
    std::cout << "Computing sum in thread: " << std::this_thread::get_id() << std::endl;
    
    int sum = 0;
    for (int num : data) {
        sum += num;
        // 模拟耗时计算
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    return sum;
}

// 另一个字符串处理函数
std::string process_string(const std::string& input, char find, char replace) {
    std::cout << "Processing string in thread: " << std::this_thread::get_id() << std::endl;
    
    std::string result = input;   
    // 用于演示的计算函数
    int compute_sum(const std::vector<int>& data) {
        std::cout << "Computing sum in thread: " << std::this_thread::get_id() << std::endl;
        
        int sum = 0;
        for (int num : data) {
            sum += num;
            // 模拟耗时计算
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        return sum;
    }
    
    // 另一个字符串处理函数
    std::string process_string(const std::string& input, char find, char replace) {
        std::cout << "Processing string in thread: " << std::this_thread::get_id() << std::endl;
        
        std::string result = input;
        for (char& c : result) {
            if (c == find) {
                c = replace;
                // 模拟耗时处理
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
        }
        
        return result;
    }
    
    int main() {
        std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
        
        // 示例1: 基本用法
        std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // 创建packaged_task，包装compute_sum函数
        std::packaged_task<int(const std::vector<int>&)> sum_task(compute_sum);
        
        // 获取关联的future
        std::future<int> sum_future = sum_task.get_future();
        
        // 在新线程中运行任务
        std::thread sum_thread(std::move(sum_task), data);
        
        // 主线程可以做其他工作
        std::cout << "Main thread continues with other work..." << std::endl;
        
        // 获取结果，如果任务未完成会阻塞
        int sum = sum_future.get();
        std::cout << "Sum result: " << sum << std::endl;
        
        // 确保线程完成
        sum_thread.join();
        
        // 示例2: 重用packaged_task
        std::packaged_task<std::string(const std::string&, char, char)> string_task(process_string);
        
        // 第一次调用
        std::future<std::string> result1 = string_task.get_future();
        
        // 注意这里: 使用std::ref包装，不能移动string_task
        std::thread t1(std::ref(string_task), "Hello World", 'o', '*');
        t1.join();
        std::cout << "First result: " << result1.get() << std::endl;
        
        // 重置packaged_task以重用
        string_task.reset();
        
        // 第二次调用
        std::future<std::string> result2 = string_task.get_future();
        std::thread t2(std::ref(string_task), "Programming is fun", 'i', '!');
        t2.join();
        std::cout << "Second result: " << result2.get() << std::endl;
        
        // 示例3: 使用lambda函数
        std::packaged_task<double(double, double)> divide_task(
            [](double a, double b) -> double {
                std::cout << "Dividing in thread: " << std::this_thread::get_id() << std::endl;
                if (b == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return a / b;
            }
        );
        
        std::future<double> divide_future = divide_task.get_future();
        
        // 在当前线程中执行任务
        try {
            divide_task(10.0, 2.0);  // 正常情况
            std::cout << "Division result: " << divide_future.get() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
        
        // 重置并尝试除以零
        divide_task.reset();
        divide_future = divide_task.get_future();
        
        try {
            divide_task(5.0, 0.0);  // 会抛出异常
            double result = divide_future.get();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
        
        return 0;
    }
    for (char& c : result) {
        if (c == find) {
            c = replace;
            // 模拟耗时处理
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
    
    return result;
}

int main() {
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
    
    // 示例1: 基本用法
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 创建packaged_task，包装compute_sum函数
    std::packaged_task<int(const std::vector<int>&)> sum_task(compute_sum);
    
    // 获取关联的future
    std::future<int> sum_future = sum_task.get_future();
    
    // 在新线程中运行任务
    std::thread sum_thread(std::move(sum_task), data);
    
    // 主线程可以做其他工作
    std::cout << "Main thread continues with other work..." << std::endl;
    
    // 获取结果，如果任务未完成会阻塞
    int sum = sum_future.get();
    std::cout << "Sum result: " << sum << std::endl;
    
    // 确保线程完成
    sum_thread.join();
    
    // 示例2: 重用packaged_task
    std::packaged_task<std::string(const std::string&, char, char)> replace_task(process_string);
    
    // 第一次调用
    std::future<std::string> result1 = replace_task.get_future();
    std::thread t1(std::ref(replace_task), "Hello World", 'o', '*');
    t1.join();
    std::cout << "First result: " << result1.get() << std::endl;
    
    // 重置packaged_task以重用
    replace_task.reset();
    
    // 第二次调用
    std::future<std::string> result2 = replace_task.get_future();
    std::thread t2(std::ref(replace_task), "Programming is fun", 'i', '!');
    t2.join();
    std::cout << "Second result: " << result2.get() << std::endl;
    
    // 示例3: 使用lambda函数
    std::packaged_task<double(double, double)> divide_task(
        [](double a, double b) -> double {
            std::cout << "Dividing in thread: " << std::this_thread::get_id() << std::endl;
            if (b == 0) {
                throw std::runtime_error("Division by zero");
            }
            return a / b;
        }
    );
    
    std::future<double> divide_future = divide_task.get_future();
    
    // 在当前线程中执行任务
    try {
        divide_task(10.0, 2.0);  // 正常情况
        std::cout << "Division result: " << divide_future.get() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    // 重置并尝试除以零
    divide_task.reset();
    divide_future = divide_task.get_future();
    
    try {
        divide_task(5.0, 0.0);  // 会抛出异常
        double result = divide_future.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}