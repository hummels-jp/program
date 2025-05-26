#include <iostream>
#include <vector>
#include <map>

int main() {
    // 自动推导基本类型
    auto x = 42;          // x 的类型是 int
    auto y = 3.14;        // y 的类型是 double
    auto z = "Hello";     // z 的类型是 const char*

    // 用于迭代器
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 用于范围 for 循环
    for (auto val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 用于复杂类型
    std::map<std::string, int> myMap = {{"one", 1}, {"two", 2}};
    for (auto pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // auto 和数组结合
    auto arr = {1, 2, 3, 4, 5}; // arr 的类型是 std::initializer_list<int>
    for (auto elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // auto 指向数组
    int myArray[] = {10, 20, 30, 40, 50};
    auto ptr = myArray; // ptr 的类型是 int*
    for (int i = 0; i < 5; ++i) {
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;

    // auto 引用指向数组
    auto& refArray = myArray; // refArray 的类型是 int (&)[5]
    for (int i = 0; i < 5; ++i) {
        std::cout << refArray[i] << " ";
    }
    std::cout << std::endl;

    // auto 指向函数指针
    int (*funcPtr)(int, int) = [](int a, int b) { return a + b; }; // 定义一个函数指针
    auto autoFuncPtr = funcPtr; // autoFuncPtr 的类型是 int (*)(int, int)
    std::cout << "Result of function pointer: " << autoFuncPtr(10, 20) << std::endl;

    // auto 引用指向函数指针
    auto& refFuncPtr = funcPtr; // refFuncPtr 的类型是 int (&)(int, int)
    std::cout << "Result of referenced function pointer: " << refFuncPtr(30, 40) << std::endl;

    return 0;
}