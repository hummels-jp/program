#include <iostream>

// 普通函数
int add(int a, int b) {
    return a + b;
}

// 函数类型定义
typedef int(FuncType)(int, int);

int main() {
    // 使用函数类型不能直接定义非指针类型的函数指针
    // FuncType func = add; // 错误：不能直接使用函数类型
    // 正确的方式是使用 typedef 定义函数指针类型
    // 函数类型没有实际的存储空间，不能实例化为变量。
    FuncType* func = add;
    std::cout << "add(2, 3) = " << func(2, 3) << std::endl;

    // 直接声明函数指针类型
    int (*func_ptr)(int, int) = add;
    std::cout << "add(5, 6) = " << func_ptr(5, 6) << std::endl;

    return 0;
}