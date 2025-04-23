#include <iostream>
#include <functional>

void normal_func(int x) {
    std::cout << "Normal function: " << x << std::endl;
}

class Demo {
public:
    void member_func(int x) {
        std::cout << "Member function: " << x << std::endl;
    }
    static void static_member_func(int x) {
        std::cout << "Static member function: " << x << std::endl;
    }
};

int main() {
    // 指向普通函数
    std::function<void(int)> f1 = normal_func;
    f1(1);

    // 指向成员函数
    Demo d;
    std::function<void(Demo&, int)> f2 = &Demo::member_func;
    f2(d, 2);

    // 也可以用 std::bind 绑定对象
    std::function<void(int)> f3 = std::bind(&Demo::member_func, &d, std::placeholders::_1);
    f3(3);

    // 指向静态成员函数
    std::function<void(int)> f4 = &Demo::static_member_func;
    f4(4);

    return 0;
}