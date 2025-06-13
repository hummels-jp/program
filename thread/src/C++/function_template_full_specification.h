#ifndef FUNCTION_TEMPLATE_FULL_SPECIFICATION_H
#define FUNCTION_TEMPLATE_FULL_SPECIFICATION_H

#include <iostream>
#include <string>

// 通用函数模板
template <typename T>
void printValue(const T& value) {
    std::cout << "Generic Template: " << value << std::endl;
}

// 全特化函数模板（针对 std::string 类型）
template <>
void printValue<std::string>(const std::string& value) {
    std::cout << "Specialized Template for std::string: " << value << std::endl;
}

#endif // FUNCTION_TEMPLATE_FULL_SPECIFICATION_H