#ifndef TEMPLATE_PARTIAL_SPECIFICATION_H
#define TEMPLATE_PARTIAL_SPECIFICATION_H

#include <iostream>
#include <string>

// 通用模板类
template <typename T1, typename T2>
class PartialTemplate {
private:
    T1 first;
    T2 second;

public:
    // 构造函数
    PartialTemplate(const T1& f, const T2& s) : first(f), second(s) {}

    // 打印值
    void print() const {
        std::cout << "Generic Template: (" << first << ", " << second << ")" << std::endl;
    }
};

// 偏特化模板类（当第二个参数为指针类型时）
template <typename T1, typename T2>
class PartialTemplate<T1, T2*> {
private:
    T1 first;
    T2* second;

public:
    // 构造函数
    PartialTemplate(const T1& f, T2* s) : first(f), second(s) {}

    // 打印值
    void print() const {
        std::cout << "Partially Specialized Template (Pointer): (" << first << ", " << *second << ")" << std::endl;
    }
};

#endif // TEMPLATE_PARTIAL_SPECIFICATION_H