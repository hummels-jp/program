#include <iostream>
#include <vector>
#include <cstddef>
#include <cassert>

// 简单的定长对象内存池
template<typename T, size_t BlockSize = 1024>
class MemoryPool {
private:
    struct Block {
        Block* next;
    };

    Block* freeList;           // 空闲链表头
    std::vector<void*> blocks; // 保存所有分配的大块内存，便于析构时释放

    void allocateBlock() {
        // 分配一大块内存
        void* newBlock = ::operator new(BlockSize * sizeof(T));
        blocks.push_back(newBlock);

        // 将新块拆分成BlockSize个Block，挂到freeList
        char* p = static_cast<char*>(newBlock);
        for (size_t i = 0; i < BlockSize; ++i) {
            Block* b = reinterpret_cast<Block*>(p + i * sizeof(T));
            b->next = freeList;
            freeList = b;
        }
    }

public:
    MemoryPool() : freeList(nullptr) {}

    ~MemoryPool() {
        for (void* block : blocks) {
            ::operator delete(block);
        }
    }

    // 分配一个对象
    T* allocate() {
        if (!freeList) {
            allocateBlock();
        }
        Block* head = freeList;
        freeList = head->next;
        return reinterpret_cast<T*>(head);
    }

    // 释放一个对象
    void deallocate(T* ptr) {
        Block* b = reinterpret_cast<Block*>(ptr);
        b->next = freeList;
        freeList = b;
    }
};

// 示例对象
struct Foo {
    int x;
    Foo(int v = 0) : x(v) { std::cout << "Foo(" << x << ") 构造\n"; }
    ~Foo() { std::cout << "Foo(" << x << ") 析构\n"; }
};

int main() {
    MemoryPool<Foo> pool;

    // 分配和释放对象
    Foo* a = pool.allocate();
    new (a) Foo(1); // 定位new，调用构造函数

    Foo* b = pool.allocate();
    new (b) Foo(2);

    a->~Foo(); // 手动析构
    pool.deallocate(a);

    b->~Foo();
    pool.deallocate(b);

    // 多次分配
    std::vector<Foo*> vec;
    for (int i = 0; i < 10; ++i) {
        Foo* f = pool.allocate();
        new (f) Foo(i * 10);
        vec.push_back(f);
    }
    for (auto f : vec) {
        f->~Foo();
        pool.deallocate(f);
    }

    return 0;
}