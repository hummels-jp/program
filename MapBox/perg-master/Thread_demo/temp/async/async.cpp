#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int compute_sum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return a + b;
}

int main() {
    std::cout << "主线程：启动异步任务...\n";

    // 创建异步任务，立即在后台线程运行 compute_sum
    std::future<int> result = std::async(std::launch::async, compute_sum, 3, 7);

    std::cout << "主线程：可以做点别的事情...\n";

    // 获取结果（如果还没完成，会阻塞等待）
    int sum = result.get();

    std::cout << "主线程：异步任务完成，结果 = " << sum << "\n";
    return 0;
}
