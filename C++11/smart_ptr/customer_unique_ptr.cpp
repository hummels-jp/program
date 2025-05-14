#include <iostream>

template<typename T>
class Unique_ptr {
private:
    T* ptr;
public:
    // 构造函数
    explicit Unique_ptr(T* p = nullptr) : ptr(p) {}

    // 禁止拷贝构造和拷贝赋值
    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

    // 移动构造
    Unique_ptr(Unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 移动赋值
    Unique_ptr& operator=(Unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~Unique_ptr() {
        delete ptr;
    }

    // 解引用操作符
    T& operator*() const {
        return *ptr;
    }

    // 箭头操作符
    T* operator->() const {
        return ptr;
    }

    // 获取原始指针
    T* get() const {
        return ptr;
    }

    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }
};

// 测试
struct Foo {
    void hello() { std::cout << "Hello, Unique_ptr!" << std::endl; }
};

int main() {
    Unique_ptr<Foo> up1(new Foo());
    up1->hello();

    Unique_ptr<Foo> up2 = std::move(up1); // 移动构造
    if (!up1.get()) {
        std::cout << "up1 已为空" << std::endl;
    }
    up2->hello();

    up2.reset();
    if (!up2.get()) {
        std::cout << "up2 已重置为空" << std::endl;
    }
    return 0;
}