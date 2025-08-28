#include <future>
#include <iostream>
using namespace std;

void worker(promise<int> _promise)
{
    this_thread::sleep_for(chrono::seconds(1));
    _promise.set_value(42);
    
}

int main()
{
    promise<int> promise;
    future<int> _future = promise.get_future();

    thread t1(worker, std::move(promise));

    cout << "main thread is free to do other things " << endl;

    shared_future<int> _shared_future = _future.share();

    int result = _shared_future.get();

    cout << "sub thread set value is " << result << endl;

    thread t2([&_shared_future](){
        cout << "thread t2 is " << _shared_future.get() << endl;
    });

    thread t3([&_shared_future](){
        cout << "thread t3 is " << _shared_future.get() << endl;
    });



    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}