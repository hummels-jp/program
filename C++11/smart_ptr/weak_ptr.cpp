#include <iostream>
#include <memory>

struct B; // 前向声明

struct A {
    std::shared_ptr<B> bptr;
    ~A() { std::cout << "A 析构\n"; }
};

struct B {
    std::weak_ptr<A> aptr; // 使用 weak_ptr 避免循环引用
    ~B() { std::cout << "B 析构\n"; }
};

void weak_ptr_demo() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->bptr = b;
    b->aptr = a;
    // 现在不会内存泄漏，A 和 B 的析构函数会被调用
}

int main() {
    weak_ptr_demo();
    std::cout << "main 结束\n";
    return 0;
}