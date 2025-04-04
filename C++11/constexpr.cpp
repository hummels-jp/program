#include <iostream>

// 定义一个使用 constexpr 的常量表达式函数
// Define a constant expression function using constexpr
constexpr int square(int x) {
    return x * x;
}

// 使用 constexpr 定义常量
// Define constants using constexpr
constexpr int value = 10;
constexpr int result = square(value);

// 定义一个 constexpr 类
// Define a constexpr class
class ConstexprClass {
public:
    constexpr ConstexprClass(int a, int b) : x(a), y(b) {}

    constexpr int sum() const {
        return x + y;
    }

private:
    int x, y;
};



int main() {
    // 在编译时计算结果
    // Compute the result at compile time
    std::cout << "Square of " << value << " is " << result << std::endl;

    // constexpr 函数也可以在运行时调用
    // constexpr functions can also be called at runtime
    int runtimeValue = 5;
    std::cout << "Square of " << runtimeValue << " is " << square(runtimeValue) << std::endl;

    // 使用 constexpr 类
    constexpr ConstexprClass obj(3, 7);
    constexpr int objSum = obj.sum();

    return 0;
}