#include <iostream>
#include <memory>

struct B; // 前向声明

struct A {
    std::shared_ptr<B> bptr;
    ~A() { std::cout << "A 析构\n"; }
};

struct B {
    std::shared_ptr<A> aptr;
    ~B() { std::cout << "B 析构\n"; }
};

void cross_reference_demo() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->bptr = b;
    b->aptr = a;
    // 由于循环引用，A 和 B 的析构函数不会被调用，内存泄漏
}

int main() {
    cross_reference_demo();
    std::cout << "main 结束\n";
    return 0;
}