#include <iostream>

// 普通函数
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    // 定义函数指针
    int (*func_ptr)(int, int);

    func_ptr = add;
    std::cout << "add(3, 5) = " << func_ptr(3, 5) << std::endl;

    func_ptr = sub;
    std::cout << "sub(3, 5) = " << func_ptr(3, 5) << std::endl;

    func_ptr = mul;
    std::cout << "mul(3, 5) = " << func_ptr(3, 5) << std::endl;

    func_ptr = divide;
    std::cout << "divide(10, 2) = " << func_ptr(10, 2) << std::endl;

    return 0;
}