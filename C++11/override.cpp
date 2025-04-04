#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() const {
        cout << "Base class show()" << endl;
    }
};

class Derived : public Base {
public:
    void show() const override { // 使用 override 关键字确保覆写基类虚函数
        cout << "Derived class show()" << endl;
    }
};

// No additional code is needed at $PLACEHOLDER$ for this functionality.
// The override keyword already ensures that the Derived class correctly overrides the Base class's virtual function.
int main() {
    Base* basePtr = new Derived();
    basePtr->show(); // 调用 Derived 的 show()
    delete basePtr;
    return 0;
}