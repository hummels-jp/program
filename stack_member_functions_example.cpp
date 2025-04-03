#include <iostream>
#include <stack>
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::stack
    std::stack<int> stk;

    // 插入元素到 stack 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        stk.push(dis(gen)); // 插入随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to push elements onto the stack: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 stack 并计时（通过 pop 模拟访问）
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    while (!stk.empty()) {
        sum += stk.top(); // 访问栈顶元素
        stk.pop();        // 移除栈顶元素
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse and pop the stack: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}