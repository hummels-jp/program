#include <iostream>
#include <string>

// 模板函数
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 多参数类型的模板函数
template <typename T1, typename T2>
auto addDifferentTypes(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// 参数个数可变的模板函数
template <typename... Args>
auto addVariadic(Args... args) -> decltype((... + args)) {
    return (... + args);
}

int main() {
    // 整数相加
    int intResult = add(3, 5);
    std::cout << "整数相加结果: " << intResult << std::endl;

    // 浮点数相加
    double doubleResult = add(2.5, 4.3);
    std::cout << "浮点数相加结果: " << doubleResult << std::endl;

    // 强制指定模板函数类型为int
    int forcedIntResult = add<int>(7.8, 2.2);
    std::cout << "强制指定模板函数类型为int的结果: " << forcedIntResult << std::endl;

    // 字符串相加
    std::string strResult = add(std::string("Hello, "), std::string("World!"));
    std::cout << "字符串相加结果: " << strResult << std::endl;

    // 多参数类型的模板函数
    auto mixedResult = addDifferentTypes(3, 4.5); // int 和 double 相加
    std::cout << "多参数类型的模板函数结果: " << mixedResult << std::endl;

    auto forcedMixedResult = addDifferentTypes<int, int>(7.8, 2.2);
    std::cout << "强制指定多参数模板函数类型为int, int的结果: " << forcedMixedResult << std::endl;

    // 参数个数可变的模板函数
    auto variadicResult = addVariadic(1, 2, 3, 4, 5); // 多个整数相加
    std::cout << "参数个数可变的模板函数结果: " << variadicResult << std::endl;
    auto variadicMixedResult = addVariadic(1.5, 2.5, 3.5); // 多个浮点数相加    
    std::cout << "参数个数可变的模板函数结果: " << variadicMixedResult << std::endl;
    
    auto forcedVariadicResult = addVariadic<int>(1.5, 2.5, 3.5); // 强制指定参数类型为int
    std::cout << "强制指定参数可变的模板函数参数类型为int的结果: " << forcedVariadicResult << std::endl;

    return 0;
}