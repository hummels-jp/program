#include <iostream>
#include <set>
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::multiset
    std::multiset<int> mset;

    // 插入元素到 multiset 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        mset.insert(dis(gen)); // 插入随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to insert elements into the multiset: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 multiset 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& val : mset) {
        sum += val; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the multiset: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 查找一个随机数并计时
    int target = dis(gen); // 生成一个随机目标值
    start = std::chrono::high_resolution_clock::now();
    auto count = mset.count(target); // 查找目标值的出现次数
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to count occurrences of " << target << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " µs" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}