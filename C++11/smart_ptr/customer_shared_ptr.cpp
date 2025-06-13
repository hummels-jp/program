#include <iostream>

template<typename T>
class Shared_ptr {
private:
    T* ptr;
    int* count;
public:
    // 构造函数
    explicit Shared_ptr(T* p = nullptr) : ptr(p), count(nullptr) {
        if (ptr) {
            count = new int(1);
        }
    }

    // 拷贝构造
    Shared_ptr(const Shared_ptr& other) : ptr(other.ptr), count(other.count) {
        if (count) {
            ++(*count);
        }
    }

    // 拷贝赋值
    Shared_ptr& operator=(const Shared_ptr& other) {
        if (this != &other) 
        {
            release();
            ptr = other.ptr;
            count = other.count;
            if (count) {
                ++(*count);
            }
        }
        return *this;
    }

    // 移动构造
    Shared_ptr(Shared_ptr&& other) noexcept : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr;
        other.count = nullptr;
    }

    // 移动赋值
    Shared_ptr& operator=(Shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~Shared_ptr() {
        release();
    }

    void release() {
        if (count) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
            ptr = nullptr;
            count = nullptr;
        }
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

    // 获取引用计数
    int use_count() const {
        return count ? *count : 0;
    }

    // 重置
    void reset(T* p = nullptr) {
        release();
        if (p) {
            ptr = p;
            count = new int(1);
        }
    }
};

// 测试
struct Foo {
    Foo() { std::cout << "Foo 构造\n"; }
    ~Foo() { std::cout << "Foo 析构\n"; }
    void hello() { std::cout << "Hello, Shared_ptr!\n"; }
};

int main() {
    Shared_ptr<Foo> sp1(new Foo());
    sp1->hello();
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

    {
        Shared_ptr<Foo> sp2 = sp1;
        std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;
        sp2->hello();
    } // sp2 离开作用域，计数减1

    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

    sp1.reset();
    std::cout << "sp1 已重置" << std::endl;

    return 0;
}