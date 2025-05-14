#include <iostream>
#include <string>

class Printer {
public:
    // 成员模板函数
    template<typename T>
    void print(const T& value) {
        std::cout << "Value: " << value << std::endl;
        std::cout << "Type: " << typeid(value).name() << std::endl; // 输出参数的类型
    }
};

int main() {
    Printer p;
    p.print(123);            // 打印 int
    p.print(3.14);           // 打印 double
    p.print("hello world");  // 打印 const char*
    std::string s = "C++";
    p.print(s);              // 打印 std::string
    return 0;
}