#ifndef TEMPLATE_PAIR_H
#define TEMPLATE_PAIR_H

#include <iostream> // 添加头文件以支持输出

template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& firstValue, const T2& secondValue) : first(firstValue), second(secondValue) {}

    // 添加 print 方法
    void print() const {
        std::cout << "Pair(" << first << ", " << second << ")" << std::endl;
    }
};

#endif // TEMPLATE_PAIR_H
