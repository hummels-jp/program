#include <iostream>

// 基类
class Base {
public:
    virtual void show() {
        std::cout << "Base class show()" << std::endl;
    }
};

// 使用 final 关键字的派生类
class Derived final : public Base {
public:
    void show() override {
        std::cout << "Derived class show()" << std::endl;
    }
};

// 试图继承 Derived 类会导致编译错误
/*
class AnotherClass : public Derived {
    // 编译错误：'Derived' class is marked 'final'
};
*/

// 使用 final 关键字禁止虚函数继承
class AnotherBase {
public:
    virtual void display() final {
        std::cout << "AnotherBase class display()" << std::endl;
    }
};

// 试图重写 display() 会导致编译错误
/*
class AnotherDerived : public AnotherBase {
public:
    void display() override {
        // 编译错误：'display' is marked 'final'
    }
};
*/

class FinalExample : public AnotherBase {
    // This class cannot override the display() method because it is marked as final in AnotherBase.
    // Any attempt to override display() here will result in a compilation error.
};

int main() {
    Derived d;
    d.show();
    return 0;
}