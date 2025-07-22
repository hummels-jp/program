#include <iostream>
#include <thread>
using namespace std;

class Sigleton_LazyMode
{
private:
    // lazy mode， dynamic create， use pointer
    static Sigleton_LazyMode* _instance;

    // construct function
    Sigleton_LazyMode()
    {}

    // copy construction
    Sigleton_LazyMode(const Sigleton_LazyMode& other) = delete;

    // copy assignment
    Sigleton_LazyMode& operator = (const Sigleton_LazyMode& other) = delete;

public:
    static Sigleton_LazyMode& get_instance()
    {
        if (_instance == nullptr)
        {
            /* code */
            _instance = new Sigleton_LazyMode();
        }

        return *_instance;  
    }
};

// static member should be initialize outside the clas
Sigleton_LazyMode* Sigleton_LazyMode::_instance = nullptr;

void thread_main()
{
    cout << "threadId: " << this_thread::get_id() << endl;
    Sigleton_LazyMode& s = Sigleton_LazyMode::get_instance();
    cout << "instance address: " << &s << endl;
}

int main()
{
    thread t1(thread_main);
    thread t2(thread_main);

    t1.join();
    t2.join();
}