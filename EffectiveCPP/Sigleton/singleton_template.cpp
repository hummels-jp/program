#include <iostream>
#include <memory>
#include <mutex>
#include <map>
using namespace std;

// 单例模式模板类，call_once + 智能指针实现
template<typename T>
class Singleton {
public:
    template<typename... Args>
    static std::shared_ptr<T> getInstance(Args&&... args) {
        std::call_once(flag_, [&]() {
            instance_ = std::make_shared<T>(std::forward<Args>(args)...);
        });
        return instance_;
    }

private:
    Singleton() = delete;
    ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::shared_ptr<T> instance_;
    static std::once_flag flag_;
};

// 静态成员初始化
template<typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

template<typename T>
std::once_flag Singleton<T>::flag_;

// 示例类
class MyClass {
public:
    MyClass(int x) : data(x) {
        cout << "MyClass(" << data << ") 构造" << endl;
    }
    void show() { cout << "MyClass data: " << data << endl; }
private:
    int data;
};

class Point {
private:
    int _x, _y;
public:
    Point(int x=0, int y=0) : _x(x), _y(y) {
        cout << "Point(" << _x << ", " << _y << ") 构造" << endl;
    }
    void show() const { cout << "Point: (" << _x << ", " << _y << ")" << endl; }
    friend struct PointKey;
};

struct PointKey {
    int x, y;
    bool operator<(const PointKey& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

class PointMultiton {
public:
    static shared_ptr<Point> getInstance(int x, int y) {
        PointKey key{x, y};
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = instances_.find(key);
        if (it != instances_.end()) {
            return it->second;
        } else {
            auto ptr = std::make_shared<Point>(x, y);
            instances_[key] = ptr;
            return ptr;
        }
    }
private:
    static std::map<PointKey, shared_ptr<Point>> instances_;
    static std::mutex mtx_;
};

std::map<PointKey, shared_ptr<Point>> PointMultiton::instances_;
std::mutex PointMultiton::mtx_;

int main() {
    auto p1 = PointMultiton::getInstance(1,2);
    auto p2 = PointMultiton::getInstance(1,2);
    auto p3 = PointMultiton::getInstance(3,4);

    cout << "p1 address: " << p1.get() << endl;
    cout << "p2 address: " << p2.get() << endl;
    cout << "p3 address: " << p3.get() << endl;
    cout << "p1 == p2? " << (p1 == p2 ? "yes" : "no") << endl;
    cout << "p1 == p3? " << (p1 == p3 ? "yes" : "no") << endl;
    return 0;
}