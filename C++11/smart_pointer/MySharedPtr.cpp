#include <iostream>
#include <atomic>
#include <string>
using namespace std;

template<typename T>
class MySharedPtr
{
private:
    T* ptr; // 指向资源的指针
    atomic<int>* ref_count; // 指向引用计数的指针

    // 释放资源
    void release()
    {
        if (ref_count != nullptr)
        {
            /* code */
            if (--(*ref_count) ==0)
            {
                /* code */
                delete ptr;
                delete ref_count;

                ptr = nullptr;
                ref_count = nullptr;
            }

            
        }
                
    }

public:
    // 1 构造函数
    MySharedPtr(T* p=nullptr)
        :ptr(p)
        ,ref_count(nullptr)
    {
        if (ptr != nullptr)
        {
            /* code */
            ref_count = new atomic<int>(1);
        }
        
    }

    // 2 拷贝构造函数
    MySharedPtr(const MySharedPtr& other)
        : ptr(other.ptr)
        , ref_count(other.ref_count)
    {
        if (ref_count !=nullptr)
        {
            /* code */
            ++(*ref_count);
        } 
    }

    // 3 移动构造函数
    MySharedPtr(MySharedPtr&& other) noexcept 
        : ptr(other.ptr)
        , ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // 4 拷贝赋值函数
    MySharedPtr& operator=(const MySharedPtr& other)
    {
        if (this == &other)
        {
            /* code */
            return *this;
        }
        else
        {
            // 如果当前指针指向资源，需要释放
            this->release();
            this->ptr = other.ptr;
            this->ref_count = other.ref_count;
            // ++(*ref_count);
            // 当前智能指针有实际管理资源，不是空指针。
            if (this->ref_count != nullptr)
            {
                /* code */
                ++(*ref_count);
            }

            return *this;
            
        }
        
    }

    // 5 移动赋值函数
    MySharedPtr& operator=(MySharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            /* code */
            this->release();
            this->ptr = other.ptr;
            this->ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;

            return *this;
        }
        
    }

    // 6 析构函数
    ~MySharedPtr()
    {
        this->release();
    }

    // 7 解引用符号
    T& operator*() const
    {
        return *ptr;
    }

    // 8 取地址符号
    T* operator->() const
    {
        return ptr;
    }

    // 9 获得原始指针
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

    // 11 判断智能指针是否有效，不为空
    explicit operator bool() const
    {
        if (ptr == nullptr)
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

class Student
{
private:
    string name;
    int age;

public:
    Student(string name = "abc", int age = 10)
        : name(name)
        , age(age)
    {
        cout << "constructor Student " << endl;
    }
    
    ~Student()
    {
        cout << "desturctor Stuedent " << endl;
    }

    void hello()
    {
        cout << "Hello from Student " << endl;
    }
};

int main()
{
    MySharedPtr<Student> st1(new Student);
    {
        MySharedPtr<Student> st2 = st1;
        cout << "st1 refcount "  << st1.get_ref_count() << endl;
        cout << "st2 refcount "  << st2.get_ref_count() << endl;
        st2->hello();
    }

    cout << "st1 refcount "  << st1.get_ref_count() << endl;

    MySharedPtr<Student> st3(std::move(st1));
    cout << "st3 refcount " << st3.get_ref_count() << endl;
    st3->hello();

}