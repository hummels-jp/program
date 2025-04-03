#include <iostream>
#include <map>
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_value(1, 1000000); // 随机生成 value 的范围

    // 定义一个 std::multimap
    std::multimap<int, int> mmap;

    // 插入元素到 multimap 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        int key = i;              // key 的值为 0 到 1000000
        int value = dis_value(gen); // 随机生成 value
        mmap.insert({key, value}); // 插入键值对
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to insert elements into the multimap: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 multimap 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& pair : mmap) {
        sum += pair.first + pair.second; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the multimap: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 查找一个随机键并计时
    std::uniform_int_distribution<> dis_key(0, 1000000); // 随机生成 key 的范围
    int target = dis_key(gen); // 生成一个随机目标键
    start = std::chrono::high_resolution_clock::now();
    auto range = mmap.equal_range(target); // 查找目标键的范围
    int count = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ++count; // 统计目标键的出现次数
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to find occurrences of key " << target << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " µs" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements (keys + values): " << sum << std::endl;

    return 0;
}