#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

int add(int a, int b) { return a + b; }

int main() {
    int a = 10;
    double b = 3.14;
    std::string s = "hello";

    // 使用decltype推断变量类型
    decltype(a) x = 20;           // int
    decltype(b) y = 6.28;         // double
    decltype(s) t = "world";      // std::string

    // 推断表达式的类型
    decltype(a + b) z = a + b;    // double

    // 推断函数返回值类型
    decltype(add(1, 2)) result = add(5, 6); // int

    std::cout << "x type: " << typeid(x).name() << ", value: " << x << std::endl;
    std::cout << "y type: " << typeid(y).name() << ", value: " << y << std::endl;
    std::cout << "t type: " << typeid(t).name() << ", value: " << t << std::endl;
    std::cout << "z type: " << typeid(z).name() << ", value: " << z << std::endl;
    std::cout << "result type: " << typeid(result).name() << ", value: " << result << std::endl;

    // decltype与auto结合
    auto v1 = 1;
    decltype(v1) v2 = 2;
    std::cout << "v2 type: " << typeid(v2).name() << ", value: " << v2 << std::endl;

    // decltype推断容器元素类型
    std::vector<int> vec{1,2,3};
    decltype(vec)::value_type elem = vec[0];
    std::cout << "elem type: " << typeid(elem).name() << ", value: " << elem << std::endl;

    return 0;
}