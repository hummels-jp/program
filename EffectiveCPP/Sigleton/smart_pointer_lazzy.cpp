#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

// 智能指针实现懒汉模式单例
class Singleton {
private:
    Singleton() { cout << "Singleton 构造" << endl; }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::unique_ptr<Singleton> instance;
    static std::mutex mtx;

public:
    static Singleton& getInstance() {
        if (!instance) {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance) {
                instance = std::make_unique<Singleton>();
            }
        }
        return *instance;
    }
    void hello() { cout << "Hello Smart Pointer Lazy Singleton!" << endl; }
};

// 静态成员初始化
std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    s1.hello();
    cout << "s1地址: " << &s1 << endl;
    cout << "s2地址: " << &s2 << endl;
    return 0;
}