#include <iostream>
using namespace std;

// 普通函数
void func(int a) {
    cout << "普通函数 func(int a) 被调用" << endl;
}

// 通用函数模板
template<typename T>
void func(T a) {
    cout << "通用函数模板 func(T a) 被调用" << endl;
}

// 具体函数模板
template<>
void func<int>(int a) {
    cout << "具体函数模板 func<int>(int a) 被调用" << endl;
}

int main() {
    func(10);      // 调用普通函数
    func('A');     // 调用通用函数模板
    func<int>('A'); // 调用具体函数模板
    func<>(20);    // 调用具体函数模板
    func<int>(30); // 调用具体函数模板
    return 0;
}