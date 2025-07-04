#include <iostream>
using namespace std;

template<typename T>
class my_unique_ptr {
private:
    T* ptr;

public:
    // 构造函数
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    // 禁止拷贝构造和拷贝赋值
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    // 移动构造
    my_unique_ptr(my_unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 移动赋值
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~my_unique_ptr() {
        delete ptr;
    }

    // 释放所有权并返回原始指针
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置为新的指针
    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // 获取原始指针
    T* get() const {
        return ptr;
    }

    // 解引用
    T& operator*() const {
        return *ptr;
    }

    // 成员访问
    T* operator->() const {
        return ptr;
    }

    // 布尔判断
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// 示例
struct Foo {
    Foo() { cout << "Foo 构造\n"; }
    ~Foo() { cout << "Foo 析构\n"; }
    void hello() { cout << "Hello from Foo\n"; }
};

int main() {
    my_unique_ptr<Foo> up1(new Foo());
    if (up1) {
        up1->hello();
    }

    my_unique_ptr<Foo> up2 = std::move(up1);
    if (!up1) {
        cout << "up1 已失去所有权\n";
    }
    if (up2) {
        (*up2).hello();
    }

    up2.reset(new Foo());
    up2->hello();

    Foo* raw = up2.release();
    if (!up2) {
        cout << "up2 已失去所有权\n";
    }
    delete raw; // 手动释放

    return 0;
}