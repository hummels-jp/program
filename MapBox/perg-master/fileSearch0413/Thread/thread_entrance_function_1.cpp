#include <iostream>
#include <thread>
using namespace std;

void funtion1() {
    std::cout << "Thread started using a common function." << std::endl;
}

class functor
{
public:
    void operator()()
    {
        cout << "functor " << endl;
    }
};

class Demo
{
public:
    void fun1()
    {
        cout << "member function " << endl;
    }

    static void fun2()
    {
        cout << "static member function " << endl;
    }
};

int main() {
    // 1. Using a common function
    std::thread thread1(funtion1);
    thread1.join(); // Wait for the thread to finish

    functor f;
    thread t2(f);
    t2.join();

    Demo d;
    thread t3(&Demo::fun1, &d);
    t3.join();
    
    thread t4(&Demo::fun2);
    t4.join();

    return 0;
}