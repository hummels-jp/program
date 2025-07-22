#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

namespace CallOnce
{
    class Sigleton
    {
    private:
        static Sigleton* _instance;
        static std::once_flag _flag;

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
            std::call_once(_flag, [](){
                _instance = new Sigleton();
            });

            return *_instance;
        }

    };

    Sigleton*  Sigleton::_instance = nullptr;
    std::once_flag Sigleton::_flag;


}

void thread_main()
{
    cout << "threadId: "  << this_thread::get_id() <<endl;
    CallOnce::Sigleton& instance = CallOnce::Sigleton::get_instance();
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



