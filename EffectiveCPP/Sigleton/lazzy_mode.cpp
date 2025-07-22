#include <iostream>
using namespace std;

// 懒汉模式单例
class Singleton {
private:
    Singleton() { cout << "Singleton 构造" << endl; }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* instance;

public:
    static Singleton& getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return *instance;
    }
    void hello() { cout << "Hello Lazy Singleton!" << endl; }
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    s1.hello();
    cout << "s1地址: " << &s1 << endl;
    cout << "s2地址: " << &s2 << endl;
    return 0;
}