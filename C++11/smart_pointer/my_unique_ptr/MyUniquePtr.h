#pragma once
#include <iostream>

template<typename T>
class MyUniquePtr
{
private:
    T* ptr;

public:
    // 1 构造函数
    MyUniquePtr(T* p = nullptr) : ptr(p) {}

    // 2 拷贝构造函数，删除
    MyUniquePtr(const MyUniquePtr& other) = delete;

    // 3 拷贝赋值函数，删除
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

    // 4 析构函数
    ~MyUniquePtr() { delete ptr; }

    // 5 释放所有权并返回原始指针
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 6 让智能指针管理新的资源，自动释放旧资源
    void reset(T* p = nullptr) {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
    }

    // 7 移动构造函数
    MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 8 移动赋值函数
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 9 解引用
    T& operator*() const { return *ptr; }

    // 10 取地址
    T* operator->() const { return ptr; }

    // 11 获得原始指针
    T* get() const { return ptr; }

    // 12 判断unique_ptr 是否不为空
    explicit operator bool() const { return ptr != nullptr; }
};