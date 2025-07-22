#include <iostream>
#include <thread>
using namespace std;

class Sigleton_HungryMode
{
private:
    // static member, when process startup, will be created;
    static Sigleton_HungryMode _instance;

    Sigleton_HungryMode()
    {}

    // copy construction
    Sigleton_HungryMode(const Sigleton_HungryMode& other) = delete;

    // copy assignment 
    Sigleton_HungryMode& operator = (const Sigleton_HungryMode& other) = delete;

public:
    static Sigleton_HungryMode& get_instance()
    {
        return _instance;
    } 
};

Sigleton_HungryMode Sigleton_HungryMode::_instance;


void thread_main()
{
    cout << "threadId: "  << this_thread::get_id() <<endl;
    Sigleton_HungryMode& instance = Sigleton_HungryMode::get_instance();
    cout << "instance address " << &instance << endl;

}

int main()
{
    thread t1(thread_main);
    thread t2(thread_main);

    t1.join();
    t2.join();

}