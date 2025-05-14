#include <iostream>
#include <memory>

struct Foo {
    Foo() { std::cout << "Foo 构造\n"; }
    ~Foo() { std::cout << "Foo 析构\n"; }
    void hello() { std::cout << "Hello, shared_ptr!\n"; }
};

int main() {
    std::shared_ptr<Foo> sp1 = std::make_shared<Foo>();
    sp1->hello();
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

    {
        std::shared_ptr<Foo> sp2 = sp1;
        std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
        sp2->hello();
    } // sp2 离开作用域，计数减1

    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

    sp1.reset();
    std::cout << "sp1 已重置" << std::endl;

    return 0;
}