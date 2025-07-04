#include <memory>
#include <iostream>
using namespace std;

template<typename T>
class MySharedPtr;

template<typename T>
class MyWeakPtr
{
    freiend class MySharedPtr;
private:
    T* ptr;
    atomic<int>* ref_count;
    atomic<int>* weak_count;

public:
    // 1 constructor
    MyWeakPtr()
        : ptr(nullptr)
        , ref_count(nullptr)
        , weak_counn(nullptr)
    {

    }

    // 2 constructor from MySharedPtr
    MyWeakPtr(const MySharedPtr<T>& shared)
        : ptr(shared.ptr)
        , ref_count(shared.ref_count)
        , weak_count(shared.weak_count)
    {
        if (weak_count !=nullptr)
        {
            /* code */
            ++(*weak_count);
        }
        
    }

    // 3 relase weak pointer
    void release()
    {
        if (weak_count !=nullptr)
        {
            /* code */
            if (--(*weak_count)==0)
            {
                /* code */
            }
            
        }
        
    }

};

template<typename T>
class MySharedPtr
{
    friend class MyWeakPtr;
private:
    T* ptr;
    atomic<int>* ref_count;
    atomic<int>* weak_count;
};