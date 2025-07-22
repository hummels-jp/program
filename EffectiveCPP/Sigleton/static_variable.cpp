#include <iostream>
using namespace std;

// 单例模式：静态局部变量实现
class Singleton {
public:
    static Singleton& instance() {
        static Singleton s; // 静态局部变量，线程安全（C++11及以后）
        return s;
    }
    void hello() { cout << "Hello Singleton!" << endl; }
private:
    Singleton() { cout << "Singleton 构造" << endl; }
    // 禁止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

int main() {
    Singleton::instance().hello();
    Singleton::instance().hello();
    return 0;
}