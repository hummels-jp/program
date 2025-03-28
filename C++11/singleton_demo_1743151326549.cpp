#include <iostream>
using namespace std;

class A
{
private:
    static A* instance;
    static int createCount; // 对象创建计数器

    A() 
    { 
        createCount++; // 每次创建对象时增加计数
    }
    A(const A& other) {}

public:
    static A* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new A();
        }
        return instance;
    }

    static int getCreateCount()
    {
        return createCount;
    }

    void say_hello()
    {
        std::cout << "hello" << std::endl;
    }
};

A* A::instance = nullptr;
int A::createCount = 0; // 初始化计数器

int main()
{
    A* a = A::getInstance();
    a->say_hello();
    A* b = A::getInstance();
    b->say_hello();

    cout << "Object created count: " << A::getCreateCount() << endl;

    return 0;
}