#include <iostream>
using namespace std;

class A
{
    private:
        static A* instance;
        A() {}
        A(const A& other){}

    public:
        static A* getInstance()
        {
            if (instance == nullptr)
            {
                instance = new A();
            }
            return instance;
        }

        void say_hello()
        {
            std::cout << "hello" << std::endl;
        }
};
A* A::instance = nullptr;

int main()
{
    A* a = A::getInstance();
    a->say_hello();
    A* b = A::getInstance();
    b->say_hello();
    return 0;
}