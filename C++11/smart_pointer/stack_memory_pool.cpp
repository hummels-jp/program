#include <iostream>
#include <stack>
#include <vector>
#include <cstddef>

// 简单的栈式内存池
template<typename T, size_t PoolSize = 1024>
class StackMemoryPool {
private:
    std::stack<T*> freeStack;  // 存储空闲内存
    std::vector<T*> allBlocks; // 用于析构时释放所有内存

public:
    StackMemoryPool() {
        // 预先分配PoolSize个对象
        for (size_t i = 0; i < PoolSize; ++i) {
            //  分配一块能存储T类型对象的原始内存，并返回T类型的指针，但此时对象还没有构造
            T* obj = reinterpret_cast<T*>(::operator new(sizeof(T)));
            freeStack.push(obj);
            allBlocks.push_back(obj);
        }
    }

    ~StackMemoryPool() {
        // 释放所有分配的内存
        for (T* obj : allBlocks) {
            ::operator delete(obj);
        }
    }

    // 分配一个对象空间，从内存池中取空间
    T* allocate() {
        if (freeStack.empty()) {
            throw std::bad_alloc();
        }
        // 
        T* obj = freeStack.top();
        freeStack.pop();
        return obj;
    }

    // 释放一个对象
    void deallocate(T* obj) {
        freeStack.push(obj);
    }
};

// 示例对象
struct Foo {
    int x;
    Foo(int v = 0) : x(v) { std::cout << "Foo(" << x << ") 构造\n"; }
    ~Foo() { std::cout << "Foo(" << x << ") 析构\n"; }
};

int main() {
    StackMemoryPool<Foo, 4> pool;

    // 分配对象
    Foo* a = pool.allocate();
    new (a) Foo(1);

    Foo* b = pool.allocate();
    new (b) Foo(2);

    // 释放对象，可以显式调用析构函数
    a->~Foo();
    pool.deallocate(a);

    b->~Foo();
    pool.deallocate(b);

    // 再次分配
    Foo* c = pool.allocate();
    new (c) Foo(3);

    c->~Foo();
    pool.deallocate(c);

    return 0;
}