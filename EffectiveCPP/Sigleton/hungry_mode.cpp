#include <iostream>
using namespace std;

// 饿汉模式单例
class Singleton {
private:
    Singleton() { cout << "Singleton 构造" << endl; }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton instance; // 静态成员，程序启动时就创建

public:
    static Singleton& getInstance() {
        return instance;
    }
    void hello() { cout << "Hello Hungry Singleton!" << endl; }
};

// 静态成员初始化
Singleton Singleton::instance;

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    s1.hello();
    cout << "s1地址: " << &s1 << endl;
    cout << "s2地址: " << &s2 << endl;
    return 0;
}