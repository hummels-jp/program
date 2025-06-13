#include <iostream>
#include <string>

// 模板函数，带有默认模板参数
template <typename T = int>
T add(T a=3, T b=4) {
    return a + b;
}

// 模板类，带有默认模板参数
template <typename T = std::string>
class Printer {
public:
    void print(const T& value="Default String") {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    // 使用模板函数，默认参数为 int
    std::cout << "add(3, 4): " << add(3, 4) << std::endl;

    // 使用模板函数，显式指定模板参数为 double
    std::cout << "add<double>(3.5, 4.5): " << add<double>(3.5, 4.5) << std::endl;

    // 使用模板类，默认参数为 std::string
    Printer<> stringPrinter;
    stringPrinter.print("Hello, World!");

    // 使用模板类，显式指定模板参数为 int
    Printer<int> intPrinter;
    intPrinter.print(42);

    return 0;
}