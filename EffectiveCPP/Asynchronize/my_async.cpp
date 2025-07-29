#include <future>
#include <iostream>
using namespace std;

int add(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(1));
    return a + b;
}

int main()
{
    future<int> _future = async(launch::async, add, 3, 4);
    shared_future<int> _shared_future = _future.share();
    cout << "Main thread is free to do other work..." << endl;

    int result = _shared_future.get();
    cout << "async result is "  << result << endl;

    thread t1([_shared_future](){
        cout << "thread t1 result is " << _shared_future.get() << endl;
    });

    thread t2([_shared_future](){
        cout << "thread t2 result is " << _shared_future.get() << endl;
    });

    t1.join();
    t2.join();

    return 0;
}