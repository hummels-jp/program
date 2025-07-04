#include <iostream>
#include <atomic>

template<typename T>
class MySharedPtr {
private:
    T* ptr;
    std::atomic<int>* ref_count;

    // 释放资源
    // 当引用计数为0时，删除指针和引用计数
    void release() {
        if (ref_count) {
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }

public:
    // 构造函数
    explicit MySharedPtr(T* p = nullptr)
        : ptr(p), ref_count(nullptr) {
        if (ptr) {
            ref_count = new std::atomic<int>(1);
        }
    }

    // 拷贝构造
    MySharedPtr(const MySharedPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    // 移动构造
    MySharedPtr(MySharedPtr&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // 拷贝赋值
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            // 释放当前对象原本所管理的资源(如果有),防止内存泄漏
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }

    // 移动赋值
    MySharedPtr& operator=(MySharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~MySharedPtr() {
        release();
    }

    // 解引用
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    int use_count() const {
        return ref_count ? ref_count->load() : 0;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// 示例
struct Foo {
    Foo() { std::cout << "Foo 构造\n"; }
    ~Foo() { std::cout << "Foo 析构\n"; }
    void hello() { std::cout << "Hello from Foo\n"; }
};

int main() {
    MySharedPtr<Foo> sp1(new Foo());
    {
        MySharedPtr<Foo> sp2 = sp1;
        std::cout << "sp1.use_count() = " << sp1.use_count() << std::endl;
        std::cout << "sp2.use_count() = " << sp2.use_count() << std::endl;
        sp2->hello();
    }
    std::cout << "sp1.use_count() = " << sp1.use_count() << std::endl;
    if (sp1) {
        sp1->hello();
    }
    return 0;
}