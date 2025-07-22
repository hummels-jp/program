
#include <iostream>
#include <thread>
using namespace std;

class Sigleton1
{
private:
    /* data */
    // make the construction function into private mode
    Sigleton1()
    {

    }

    // delete copy construction function
    Sigleton1(const Sigleton1& other) = delete;
    // delete copy assignment construction function
    Sigleton1& operator = (const Sigleton1& other) = delete;

public:
    // get the unique sigleton
    static Sigleton1& getInst()
    {
        static Sigleton1 instance;
        return instance;
    }
};

void thread_main()
{
    Sigleton1& s1 = Sigleton1::getInst();
    cout << "s1 address " << &s1 << endl;
}

int main()
{


    // Sigleton1& s2 = Sigleton1::getInst();
    // cout << "s2 address " << &s2 << endl;
    thread t1([](){
        cout << this_thread::get_id() << endl;
        Sigleton1& s1 = Sigleton1::getInst();
        cout << "s1 address " << &s1 << endl;
    });

    thread t2([](){
        cout << this_thread::get_id() << endl;
        Sigleton1& s1 = Sigleton1::getInst();
        cout << "s1 address " << &s1 << endl;
    });

    t1.join();
    t2.join();
}



