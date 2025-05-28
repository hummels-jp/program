#include <iostream>
#include <utility>
using namespace std;

// 被调用的目标函数
void forwardTo(int& x) {
    std::cout << "Lvalue reference: " << x << std::endl;
}

void forwardTo(int&& x) {
    std::cout << "Rvalue reference: " << x << std::endl;
}

// 一个通用的函数模板，用于完美转发
template <typename T>
void process(T&& arg) {
    // 调用另一个函数，并使用 std::forward 保留参数的值类别
    forwardTo(std::forward<T>(arg));
}

int main() {
    int a = 10;

    // 传递左值
    process(a);

    // 传递右值
    process(20);

    return 0;
}