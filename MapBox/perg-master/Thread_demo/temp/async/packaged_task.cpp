#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// 一个简单的函数，用于计算平方
int square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return x * x;
}

int main() {
    // 用 std::packaged_task 包装函数
    std::packaged_task<int(int)> task(square);

    // 获取与任务关联的 future
    std::future<int> result = task.get_future();

    // 将任务移动到一个新线程中执行
    std::thread t(std::move(task), 5);

    std::cout << "任务正在后台执行...\n";

    // 等待任务完成，并获取结果
    int value = result.get();
    std::cout << "任务完成，结果为: " << value << "\n";

    // 确保线程完成
    t.join();

    return 0;
}