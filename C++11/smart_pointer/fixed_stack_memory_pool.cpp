// 固定长度的栈内存池

#include <stack>
#include <vector>
#include <iostream>
using namespace std;

template<typename T, size_t pool_size = 1024>
class fixed_stack_memory_pool
{
private:
    stack<T*> freeBlocks; // 存储当前可用的空间
    vector<T*>  allBlocks; // 存储所有分配的空间，方便回收

public:
    // 1 构造函数， 根据pool_size, 预先分配空间
    fixed_stack_memory_pool()
    {
        for (int i = 0; i < pool_size; i++)
        {
            /* code */
            T* obj = (T*)malloc(sizeof(T));
            freeBlocks.push(obj);
            allBlocks.push_back(obj);
        }
        
    }

    // 2 析构函数， 清除所分配的所有内存
    ~fixed_stack_memory_pool()
    {
        for (T* obj: allBlocks)
        {
            /* code */
            free(obj);
        }
        
    }

    // 3 allocate 申请内存，从freeBlocks上提取一个
    T* allocate()
    {
        if (freeBlocks.empty())
        {
            /* code */
            throw bad_alloc();
        }

        T* obj = freeBlocks.top();
        freeBlocks.pop();
        return obj;
        
    }

    // 4 deallocate 释放内存，加入到freeBlocks中
    void deallocate(T* obj)
    {
        freeBlocks.push(obj);
    }
};

// 示例对象
struct Foo {
    int x;
    Foo(int v = 0) : x(v) { std::cout << "Foo(" << x << ") 构造\n"; }
    ~Foo() { std::cout << "Foo(" << x << ") 析构\n"; }
};


int main() {

    fixed_stack_memory_pool<Foo, 3> pool;
    Foo* a = pool.allocate();
    // 在指定内存处，进行对象构造
    new(a) Foo(1);

    Foo* b = pool.allocate();
    new(b) Foo(2);

    Foo* c = pool.allocate();
    new(c) Foo(3);

    c->~Foo();
    pool.deallocate(c);

    Foo* d = pool.allocate();
    new(d) Foo(4);

    


    return 0;
}
