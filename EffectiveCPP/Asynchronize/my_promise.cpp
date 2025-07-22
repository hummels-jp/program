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
    int result = _future.get();

    cout << "sub thread set value is " << result << endl;

    t1.join();
    return 0;
}