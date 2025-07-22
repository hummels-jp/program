#include <iostream>
#include <type_traits>
using namespace std;

// 检测类是否有成员函数 foo 的模板元编程
template<typename, typename = void>
struct has_foo : std::false_type {};

template<typename T>
struct has_foo<T, std::void_t<decltype(std::declval<T>().foo())>> : std::true_type {};

// 测试类
struct A {
    void foo() {}
};

struct B {
    void bar() {}
};

int main() {
    cout << std::boolalpha;
    cout << "A has foo: " << has_foo<A>::value << endl; // true
    cout << "B has foo: " << has_foo<B>::value << endl; // false

    // 也可以用 static_assert
    static_assert(has_foo<A>::value, "A should have foo");
    static_assert(!has_foo<B>::value, "B should not have foo");
    return 0;
}