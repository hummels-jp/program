#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

// 模板函数，参数类型由实参自动推导
template<typename T>
void parameter_reference(const T& value) {
    cout << "Value: " << value << endl;
    cout << "Type: " << typeid(value).name() << endl; // 输出参数的类型
    // cout << "Twice: " << value * 2 << endl; // 假设 T 支持乘法操作
}

// 普通函数
template<typename R, typename T1, typename T2>
void parameter_reference2(R(*func)(T1, T2))
 {
    cout << typeid(R).name() << endl; // 输出函数返回值类型
    cout << typeid(T1).name() << endl; // 输出函数参数类型
    cout << typeid(T2).name() << endl; // 输出函数参数类型


}

int sum(int a, int b) {
    return a + b;
}

int main() {
    parameter_reference(42);           // 推导为 int
    parameter_reference(3.14);         // 推导为 double
    parameter_reference("hello");      // 推导为 const char*
    std::string s = "world";
    parameter_reference(s);            // 推导为 std::string

    parameter_reference(sum(1, 2));    // 推导为 int
    parameter_reference(sum);          // 推导为 int(*)(int, int): PFdiiE

    parameter_reference2(sum);   // 推导为 int(*)(int, int): PFdiiE

    return 0;
}