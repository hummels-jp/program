#include <iostream>

class Fraction {
private:
    int m_numerator;   // 分子
    int m_denominator; // 分母
public:
    // 构造函数
    Fraction() : m_numerator(0), m_denominator(1) {}

    // 带参数的构造函数
    Fraction(int numerator, int denominator) 
        : m_numerator(numerator), m_denominator(denominator) {}

    
    Fraction(std::initializer_list<int> list) {
        auto it = list.begin();
        m_numerator = (it != list.end()) ? *it : 0;
        m_denominator = (it + 1 != list.end()) ? *(it + 1) : 1;
    }

    // 重载类型转换运算符 double
    operator double() const {
        return static_cast<double>(m_numerator) / m_denominator;
    }

    // 重载类型转换运算符 int
    operator int() const {
        return m_numerator / m_denominator;
    }
};

int main() {
    Fraction f(3,4); // 分子为3，分母为4
    double d = f; // 调用operator double() - Ensure this is inside the main function
    int i = f;    // 调用operator int()
    
    std::cout << "Fraction as double: " << d << std::endl;
    std::cout << "Fraction as int: " << i << std::endl;

    return 0;
}