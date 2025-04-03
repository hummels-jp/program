#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::sort
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::vector
    std::vector<int> vec;

    vec.max_size(); // 触发 max_size() 的计算
    std::cout << "Max size of vector: " << vec.max_size() << std::endl;

    // 填充 vector 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        vec.push_back(dis(gen)); // 填充随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the vector: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 排序 vector 并计时
    start = std::chrono::high_resolution_clock::now();
    std::sort(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to sort the vector: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 vector 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& val : vec) {
        sum += val; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the vector: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}