#include <iostream>
#include <forward_list>
#include <algorithm> // 用于 std::sort
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::forward_list
    std::forward_list<int> flist;

    std::cout << "Max size of forward_list: " << flist.max_size() << std::endl;

    // 填充 forward_list 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        flist.push_front(dis(gen)); // 使用 push_front 填充随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the forward_list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 排序 forward_list 并计时
    start = std::chrono::high_resolution_clock::now();
    flist.sort(); // 使用 forward_list 的成员函数 sort
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to sort the forward_list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 forward_list 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& val : flist) {
        sum += val; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the forward_list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}