#include <iostream>
#include <atomic>

template<typename T>
class MySharedPtr; // 前向声明

template<typename T>
class MyWeakPtr {
    friend class MySharedPtr<T>; 
private:
    T* ptr;
    std::atomic<int>* ref_count; // 强引用计数
    std::atomic<int>* weak_count; // 弱引用计数

public:
    // 构造函数
    MyWeakPtr() : ptr(nullptr), ref_count(nullptr), weak_count(nullptr) {}

    // 由MySharedPtr构造 由 shared_ptr 构造
    MyWeakPtr(const MySharedPtr<T>& shared)
        : ptr(shared.ptr), ref_count(shared.ref_count), weak_count(shared.weak_count) {
        if (weak_count) ++(*weak_count);
    }

    // 拷贝构造
    MyWeakPtr(const MyWeakPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (weak_count) ++(*weak_count);
    }

    // 拷贝赋值
    MyWeakPtr& operator=(const MyWeakPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (weak_count) ++(*weak_count);
        }
        return *this;
    }

    // 析构
    ~MyWeakPtr() {
        release();
    }

    void release() {
    if (weak_count) 
    { // 如果有弱引用计数指针
        if (--(*weak_count) == 0 && (!ref_count || *ref_count == 0)) 
        {
            // 如果弱引用计数减到0，并且没有强引用（ref_count为0或nullptr）
            delete weak_count; // 释放弱引用计数内存
        }
        weak_count = nullptr; // 置空，防止悬挂指针
    }
    ptr = nullptr;        // 置空原始指针
    ref_count = nullptr;  // 置空强引用计数指针
    }

    // 判断资源是否已被释放， 弱引用指针观察的是强引用指针
    bool expired() const {
        return !ref_count || *ref_count == 0;
    }

    // 尝试提升为MySharedPtr
    MySharedPtr<T> lock() const {
        if (!expired()) {
            return MySharedPtr<T>(*this);
        }
        return MySharedPtr<T>();
    }
};

// 简单的MySharedPtr实现，支持weak_ptr
template<typename T>
class MySharedPtr {
    friend class MyWeakPtr<T>;
private:
    T* ptr;
    std::atomic<int>* ref_count;
    std::atomic<int>* weak_count;

    void release() {
        if (ref_count) { // 如果有强引用计数指针
            if (--(*ref_count) == 0) { // 强引用计数减到0
                delete ptr; // 释放资源
                if (weak_count && *weak_count == 0) { // 如果弱引用计数也为0
                    delete ref_count; // 释放强引用计数内存
                    delete weak_count; // 释放弱引用计数内存
                }
            }
            ptr = nullptr;        // 置空原始指针
            ref_count = nullptr;  // 置空强引用计数指针
            weak_count = nullptr; // 置空弱引用计数指针
        }
    }

public:
    //  构造函数
    MySharedPtr(T* p = nullptr)
        : ptr(p), ref_count(nullptr), weak_count(nullptr) {
        if (ptr) {
            ref_count = new std::atomic<int>(1);
            weak_count = new std::atomic<int>(0);
        }
    }

    // 由weak_ptr提升
    MySharedPtr(const MyWeakPtr<T>& weak)
        : ptr(weak.ptr), ref_count(weak.ref_count), weak_count(weak.weak_count) {
        if (ref_count && *ref_count > 0) ++(*ref_count);
        else ptr = nullptr; // 资源已释放
    }

    // 拷贝构造
    MySharedPtr(const MySharedPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (ref_count) ++(*ref_count);
    }

    // 拷贝赋值
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (ref_count) ++(*ref_count);
        }
        return *this;
    }

    // 析构
    ~MySharedPtr() {
        release();
    }

    // operator *
    T& operator*() const { return *ptr; }
    // operator ->, get the address
    T* operator->() const { return ptr; }
    // get the original pointer
    T* get() const { return ptr; }
    // get the strong reference count
    int use_count() const { return ref_count ? ref_count->load() : 0; }
    // wheather the pointer is not null
    explicit operator bool() const { return ptr != nullptr; }
};

// 示例
struct Foo {
    Foo() { std::cout << "Foo 构造\n"; }
    ~Foo() { std::cout << "Foo 析构\n"; }
    void hello() { std::cout << "Hello from Foo\n"; }
};

int main() {
    MySharedPtr<Foo> sp(new Foo());
    MyWeakPtr<Foo> wp = sp;

    std::cout << "use_count: " << sp.use_count() << std::endl;
    {
        MySharedPtr<Foo> sp2 = wp.lock();
        if (sp2) {
            sp2->hello();
            std::cout << "use_count: " << sp2.use_count() << std::endl;
        }
    }
    // sp.~MySharedPtr(); // 不要手动调用析构函数！
    // 让sp离开作用域自动析构即可
    if (wp.expired()) {
        std::cout << "资源已释放" << std::endl;
    } else {
        std::cout << "资源仍然存在" << std::endl;
    }
    return 0;
}