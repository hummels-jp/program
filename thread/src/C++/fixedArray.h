#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H

#include <iostream> // 用于输出
#include <stdexcept> // 用于异常处理

// 定义模板类 FixedArray
template <typename T, std::size_t N>
class FixedArray {
private:
    T data[N]; // 固定大小的数组

public:
    // 默认构造函数
    FixedArray() = default;

    // 获取数组大小
    constexpr std::size_t size() const {
        return N;
    }

    // 重载下标运算符（非 const 版本）
    T& operator[](std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 重载下标运算符（const 版本）
    const T& operator[](std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 打印数组内容
    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < N; ++i) {
            std::cout << data[i];
            if (i < N - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

#endif // FIXEDARRAY_H