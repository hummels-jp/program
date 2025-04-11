#include <iostream>

// 仿函数类：有参数、有返回值
class Multiply {
private:
    int factor;

public:
    // 构造函数：设定因子
    Multiply(int f) : factor(f) {}

    // 重载 operator()，使对象可以像函数一样调用
    int operator()(int value) const {
        return value * factor;
    }
};


int main() {
    Multiply times3(3);  // 创建一个仿函数对象，因子为 3
    Multiply times5(5);

    int result = times3(5);  // 相当于调用 times3.operator()(5)
    int result1 = times5(5);

    std::cout << "5 * 3 = " << result << std::endl;
    std::cout << "5 * 5 = " << result1 << std::endl;

    return 0;
}
