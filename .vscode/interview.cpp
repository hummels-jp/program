#include <iostream>
using namespace std;

class Base0 {
};

class Base1 {
public:
    virtual void func() {
        cout << "Base1::func()" << endl;
    }
};

class Base2 {
public:
    virtual void func() {
        cout << "Base2::func()" << endl;
    }
};

class Derived1 : public Base1{

};

class Derived2 : public Base2{

};

class Derived3 : public Derived1, public Derived2 {
public:
    void func() override {
        cout << "Derived3::func()" << endl;
    }
};
