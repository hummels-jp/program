#pragma once
#include <iostream>
#include <string>

// 函数模板
template <typename T>
void printValue(const T& value) {
    std::cout << "Generic template: " << value << std::endl;
}

// 函数模板的全特化
template <>
void printValue(const std::string& value) {
    std::cout << "Specialized template for std::string: " << value << std::endl;
}