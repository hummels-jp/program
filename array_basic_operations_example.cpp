#include <iostream>
#include <array>
#include <algorithm> // 用于 std::sort
#include <chrono> // 用于计时

const int NUM_ELEMENTS = 1000000; // 全局变量定义元素个数

int main() {
    try {
        // 定义一个 std::array
        std::array<int, NUM_ELEMENTS>* arr = nullptr;

        // 检查内存分配是否成功
        try {
            arr = new std::array<int, NUM_ELEMENTS>();
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            return 1;
        }

        // 填充数组并计时
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < NUM_ELEMENTS; ++i) {
            (*arr)[i] = NUM_ELEMENTS - i; // 填充递减的值
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken to fill the array: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        // 排序数组并计时
        start = std::chrono::high_resolution_clock::now();
        std::sort(arr->begin(), arr->end());
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken to sort the array: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        // 遍历数组并计时
        start = std::chrono::high_resolution_clock::now();
        long long sum = 0;
        for (const auto& val : *arr) {
            sum += val; // 模拟访问操作
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken to traverse the array: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        // 输出总和（防止优化）
        std::cout << "Sum of elements: " << sum << std::endl;

        // 释放内存
        delete arr;

    } catch (const std::exception& e) {
        std::cerr << "Standard exception occurred: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
