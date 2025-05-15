#include <iostream>

class Demo {
public:
    void show() {
        std::cout << "Non-const show()" << std::endl;
        showConst(); // 调用const版本成员函数
    }

    void showConst() const {
        std::cout << "Const showConst()" << std::endl;
    }
};

int main() {
    Demo d;
    d.show(); // 调用非const成员函数，内部调用const成员函数

    const Demo cd;
    cd.showConst(); // 调用const成员函数
    // cd.show(); // 错误：不能调用非const成员函数， 非const成员函数可能会修改对象的状态

    return 0;
}