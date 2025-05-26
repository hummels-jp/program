#include <iostream>

int main() {
    // 使用 decltype 关键字来推断变量的类型
    int x = 42;
    decltype(x) y = x; // y has the same type as x (int)

    std::cout << "x: " << x << ", y: " << y << std::endl;

    y = 100; // Modify y
    std::cout << "After modifying y:" << std::endl;
    std::cout << "x: " << x << ", y: " << y << std::endl;

    // 使用 decltype 推断函数返回类型
    auto add = [](int a, int b) -> decltype(a + b) {
        return a + b;
    };

    // 使用 decltype 推断函数参数类型
    auto multiply = [](decltype(x) a, decltype(y) b) {
        return a * b;
    }; 
    
    // 调用函数并输出结果
    std::cout << "Addition: " << add(x, y) << std::endl;



    return 0;
}