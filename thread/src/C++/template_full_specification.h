#ifndef TEMPLATE_FULL_SPECIFICATION_H
#define TEMPLATE_FULL_SPECIFICATION_H

#include <iostream>
#include <string>

// 通用模板类
template <typename T>
class MyTemplate {
private:
    T value;

public:
    // 构造函数
    MyTemplate(const T& val) : value(val) {}

    // 打印值
    void print() const {
        std::cout << "Generic Template: " << value << std::endl;
    }
};

// 全特化模板类（针对 std::string 类型）
template <>
class MyTemplate<std::string> {
private:
    std::string value;

public:
    // 构造函数
    MyTemplate(const std::string& val) : value(val) {}

    // 打印值
    void print() const {
        std::cout << "Specialized Template for std::string: " << value << std::endl;
    }
};

#endif // TEMPLATE_FULL_SPECIFICATION_H