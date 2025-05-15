#include <iostream>
#include <typeinfo>
#include <type_traits>
using namespace std;

// 值传递
template<typename T>
void func_value(T arg) {
    cout << "func_value: T = " << typeid(T).name() << ", arg = " << typeid(arg).name();
    if (std::is_const<T>::value)
        cout << " | T is const";
    else
        cout << " | T is not const";
    cout << endl;
}

// 左值引用传递
template<typename T>
void func_lref(T& arg) {
    cout << "func_lref: T = " << typeid(T).name() << ", arg = " << typeid(arg).name();
    if (std::is_const<T>::value)
        cout << " | T is const";
    else
        cout << " | T is not const";
    cout << endl;
}

// 右值引用传递
template<typename T>
void func_rref(T&& arg) {
    cout << "func_rref: T = " << typeid(T).name() << ", arg = " << typeid(arg).name();
    if (std::is_const<T>::value)
        cout << " | T is const";
    else
        cout << " | T is not const";
    if (std::is_lvalue_reference<decltype(arg)>::value) {
        cout << " | arg is an lvalue inside the function";
    } else {
        cout << " | arg is an rvalue reference inside the function";
    }
    cout << endl;
}

int main() {
    int a = 10;
    int& ref = a;

    // func_value(a);      // T = int
    // func_value(ref);    // T = int

    // func_lref(a);       // T = int
    // func_lref(ref);     // T = int

    // func_rref(20);      // T = int
    // func_rref(a);       // T = int
    // func_rref(std::move(a)); // T = int

    const int b = 20;
    const int& cref = b;
    func_value(a);      // T = int
    func_value(b);       // T = const int
    func_value(cref);    // T = const int

    func_lref(b);       // T = const int
    func_lref(cref);    // T = const int

    func_rref(20);      // T = int
    func_rref(b);       // T = const int
    func_rref(cref);    // T = const int
    return 0;
}