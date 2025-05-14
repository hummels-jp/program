#include <iostream>
#include <string>

// 普通函数声明（通常放在头文件）
void printInt(int a);

// 模板函数声明（未特化，声明和定义都应在头文件）
template<typename T>
void print(const T& value) {
    std::cout << "模板函数: " << value << std::endl;
}

// 模板特化声明（通常放在头文件）
template<>
void print<std::string>(const std::string& value);

// 普通函数实现（通常放在源文件）
void printInt(int a) {
    std::cout << "普通函数: " << a << std::endl;
}

// 模板特化实现（通常放在源文件）
template<>
void print(const std::string& value) {
    std::cout << "模板特化: " << value << std::endl;
}

int main() {
    printInt(10);                // 普通函数
    print(3.14);                 // 模板函数
    print<std::string>("hello"); // 模板特化
    std::string s = "world";
    print(s);                    // 模板特化
    return 0;
}