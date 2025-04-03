#include <iostream>
#include <deque>
#include <algorithm> // 用于 std::sort
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::deque
    std::deque<int> deq;

    // 填充 deque 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        deq.push_back(dis(gen)); // 使用 push_back 填充随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the deque: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 排序 deque 并计时
    start = std::chrono::high_resolution_clock::now();
    std::sort(deq.begin(), deq.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to sort the deque: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 deque 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& val : deq) {
        sum += val; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the deque: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 查找一个数并计时
    int target = dis(gen); // 随机生成一个目标数
    start = std::chrono::high_resolution_clock::now();
    auto it = std::find(deq.begin(), deq.end(), target);
    end = std::chrono::high_resolution_clock::now();
    if (it != deq.end()) {
        std::cout << "Target " << target << " found in the deque." << std::endl;
    } else {
        std::cout << "Target " << target << " not found in the deque." << std::endl;
    }
    std::cout << "Time taken to find the target: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}