#include <iostream>

class Base0 {
public:
    virtual void foo() {
        std::cout << "Base0::foo()\n";
    }
};

class Base1 {
public:
    virtual void foo() {
        std::cout << "Base1::foo()\n";
    }
};

class Derived1 : public Base1 {
};

class Derived2 : public Base1 {
public:
    virtual void foo() {
        std::cout << "Derived2::foo()\n";
    }

    virtual void bar() {
        std::cout << "Derived2::bar()\n";
    }
};

class Base2 {
public:
    virtual void foo() {
        std::cout << "Base2::foo()\n";
    }
};

class Derived3 : public Base1, public Base2 {
};

int main() {
    std::cout << sizeof(Base0) << std::endl;
    std::cout << sizeof(Base1) << std::endl;
    std::cout << sizeof(Derived1) << std::endl;
    std::cout << sizeof(Derived2) << std::endl;
    std::cout << sizeof(Derived3) << std::endl;

    Base1 b1;
    Base1 &pb1 = b1;
    Base1 *pd1 = new Derived1;
    Derived2 d2;

    return 0;
}