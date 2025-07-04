#include <iostream>
#include <atomic>
using namespace std;

template<typename T>
class my_shared_ptr 
{
private:
    T* ptr;  // 指向资源的指针
    std::atomic<int>* ref_count; // 指向资源的引用计数


    // 0 释放资源
    void realease()
    {
        if (--(*ref_count) ==0)
        {
            /* code */
            delete ptr;
            delete ref_count;
        }
        
    }
public:
    // 1 构造函数
    // explict 关键字，可以避免隐式转换
    explicit my_shared_ptr(T* p = nullptr ):
        ptr(p), 
        ref_count(nullptr)
    {
        if (ptr !=nullptr)
        {
            ref_count = new atomic<int>(1);
            /* code */
        }
        
    }

    // 2 拷贝构造函数
    my_shared_ptr(const my_shared_ptr& other)
        :ptr(other.ptr), 
        ref_count(other.ref_count)
    {
        if (ref_count != nullptr)
        {
            /* code */
            ++(*ref_count);
        }
        
    }

    // 3 移动构造函数
    // noexcept 关键字，不抛出异常
    my_shared_ptr(my_shared_ptr&& other) noexcept
        : ptr(other.ptr)
        , ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // 4 拷贝赋值
    my_shared_ptr&  operator=(const my_shared_ptr& other)
    {
        // 自己给自己赋值
        if (this == &other)
        {
            /* code */
            return *this;
        }
        else
        {
            // 释放当前对象所管理的资源，如果有，防止内存泄漏
            this->realease();
            this->ptr = other.ptr;
            this->ref_count = other.ref_count;
            if (this->ref_count)
            {
                /* code */
                ++(*this->ref_count);
            }
            
        } 

        return *this;
    }

    // 5 移动赋值
    my_shared_ptr& operator=(my_shared_ptr&& other) noexcept
    {
        if (this == &other)
        {
            /* code */
            return *this;
        }
        else
        {
            this->ptr = other.ptr;
            this->ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;

            return *this;
        }
        
    }

    // 6 析构函数
    ~my_shared_ptr()
    {
        this->realease();
    }

    // 7 解引用, 重载运算符 *
    T& operator*() const
    {
        return *ptr;
    }

    // 8 取地址， 重载运算符 ->
    T* operator->() const
    {
        return ptr;
    }

    // 9 获得原始指针， get
    T* get() const
    {
        return ptr;
    }

    // 10 获得引用计数
    int get_ref_count() const
    {
        if (this->ref_count == nullptr)
        {
            /* code */
            return 0;
        }
        else
        {
            return ref_count->load();
        }
        
    }

    // 11 判断智能指针是否有效，是否管理着对象，重载符号()
    explicit operator bool() const
    {
        if (this->ptr == nullptr)
        {
            /* code */
            return false;
        }
        else
        {
            return true;
        }
        
    }
};


// 示例
struct Foo {
    Foo() { std::cout << "Foo 构造\n"; }
    ~Foo() { std::cout << "Foo 析构\n"; }
    void hello() { std::cout << "Hello from Foo\n"; }
};

int main() {

    // 1 拷贝复制
    my_shared_ptr<Foo> sp1(new Foo());
    {
        my_shared_ptr<Foo> sp2 = sp1;
        cout << "sp1 ref count " << sp1.get_ref_count() << endl;
        cout << "sp2 ref count " << sp2.get_ref_count() << endl;
        sp2->hello();
    }

    cout << "sp1 ref count " << sp1.get_ref_count() << endl;

    return 0;
}