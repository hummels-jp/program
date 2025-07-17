#include <iostream>
using namespace std;

// 普通类模板
template<typename T>
class Box {
public:
    Box(T v) : value(v) {}
    void show() const { cout << "Box: " << value << endl; }
private:
    T value;
};

// 全特化：当类型为 const char* 时
template<>
class Box<const char*> {
public:
    Box(const char* v) : value(v) {}
    void show() const { cout << "Box (const char*): " << value << endl; }
private:
    const char* value;
};

// 偏特化：当类型为指针时
template<typename T>
class Box<T*> {
public:
    Box(T* v) : value(v) {}
    void show() const { cout << "Box (pointer): " << *value << endl; }
private:
    T* value;
};

int main() {
    Box<int> b1(123);
    b1.show(); // Box: 123

    Box<const char*> b2("hello");
    b2.show(); // Box (const char*): hello

    int x = 456;
    Box<int*> b3(&x);
    b3.show(); // Box (pointer): 456

    return 0;
}