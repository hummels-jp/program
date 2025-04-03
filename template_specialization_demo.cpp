#include <iostream>
#include <string>
using namespace std;

// 通用模板
template <typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << "Generic Printer: " << value << std::endl;
    }
};

// 偏特化：针对指针类型， 范围特化
template <typename T>
class Printer<T*> {
public:
    void print(T* value) {
        if (value) {
            std::cout << "Pointer Printer: " << *value << std::endl;
        } else {
            std::cout << "Pointer Printer: nullptr" << std::endl;
        }
    }
};

// 偏特化：针对 `std::string`， 类型特化
template <>
class Printer<std::string> {
public:
    void print(const std::string& value) {
        std::cout << "String Printer: " << value << std::endl;
    }
};

int main() {
    Printer<int> intPrinter;
    intPrinter.print(42); // 使用通用模板

    int x = 10;
    Printer<int*> pointerPrinter;
    pointerPrinter.print(&x); // 使用指针类型的偏特化

    Printer<std::string> stringPrinter;
    stringPrinter.print("Hello, Templates!"); // 使用 std::string 的偏特化

    return 0;
}
