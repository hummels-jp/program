#include <iostream>
#include <mutex>
using namespace std;

// 线程安全的懒汉模式单例
class Singleton {
private:
    Singleton() { cout << "Singleton 构造" << endl; }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* instance;
    static std::mutex mtx;

public:
    static Singleton& getInstance() {
        if (!instance) {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance) { // 双重检查锁定
                instance = new Singleton();
            }
        }
        return *instance;
    }
    void hello() { cout << "Hello Thread Safe Lazy Singleton!" << endl; }
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    s1.hello();
    cout << "s1地址: " << &s1 << endl;
    cout << "s2地址: " << &s2 << endl;
    return 0;
}