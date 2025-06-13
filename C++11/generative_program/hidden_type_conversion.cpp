#include <iostream>
using namespace std;

template<typename T>
void func(T a) {
    cout << "T = " << typeid(T).name() << ", a = " << a << endl;
}

int main() {
    char ch = 'A';
    int n = 100;

    // 自动类型推导，不发生隐式类型转换
    func(ch); // T = char

    // 显式指定模板参数，发生隐式类型转换
    func<int>(ch); // T = int，ch 被提升为 int

    // 自动类型推导，不发生隐式类型转换
    func(n); // T = int

    // 显式指定模板参数，发生隐式类型转换
    func<double>(n); // T = double，n 被提升为 double

    return 0;
}