
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
using namespace std;

namespace SmartPointer
{
    class Sigleton
    {
    private:
        static shared_ptr<Sigleton> _instance;
        static mutex _mutex;

        Sigleton()
        {

        }

        Sigleton(const Sigleton& other) = delete;

        Sigleton& operator = (const Sigleton& other) = delete;

    public:
        static Sigleton& get_instance()
        {
            if (_instance != nullptr)
            {
                /* code */
                return *_instance;
            }
            else
            {
                lock_guard<mutex> lock(_mutex);
                if (_instance!=nullptr)
                {
                    return *_instance;
                    /* code */
                }
                else
                {
                    // _instance = std::make_shared<SmartPointer::Sigleton>();
                    _instance = shared_ptr<Sigleton>(new Sigleton());
                }
                
            }
            return *_instance;
            
        }
    };

    shared_ptr<Sigleton> Sigleton::_instance = nullptr;
    mutex Sigleton::_mutex;
}

void thread_main()
{
    cout << "threadId: "  << this_thread::get_id() <<endl;
    SmartPointer::Sigleton& instance = SmartPointer::Sigleton::get_instance();
    cout << "instance address " << &instance << endl;

}

int main()
{
    thread t1(thread_main);
    thread t2(thread_main);

    t1.join();
    t2.join();

    return 0;
}