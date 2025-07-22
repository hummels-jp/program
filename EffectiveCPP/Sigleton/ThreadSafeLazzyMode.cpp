#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


class Sigleton
{
private:
    static Sigleton* _instance;
    static mutex _mutex;
    // construction
    Sigleton()
    {

    }

    // copy construction 
    Sigleton(const Sigleton& other) = delete;

    // copy assignment
    Sigleton& operator = (const Sigleton& other) = delete;

public:
    static Sigleton& get_instance()
    {
        if (_instance !=nullptr)
        {
            /* code */
            return *_instance;
        }
        else
        {
            lock_guard<mutex> lock(_mutex);
            if (_instance != nullptr)
            {
                /* code */
                return *_instance;
            }
            else
            {
                _instance = new Sigleton();
            }
            
        }
        
        return *_instance;
    }
};

Sigleton* Sigleton::_instance = nullptr;
mutex Sigleton::_mutex;

void thread_main()
{
    cout << "threadId: " << this_thread::get_id() << endl;
    Sigleton& s = Sigleton::get_instance();
    cout << "instance address" << &s << endl;
}

int main()
{
    thread t1(thread_main);
    thread t2(thread_main);

    t1.join();
    t2.join();
}