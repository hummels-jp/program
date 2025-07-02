#include <thread>
#include <iostream>
#include <future>
#include <chrono>
using namespace std;

// the sub thread callback function
int worker()
{
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "worker down " << endl;
    return 10;
}

int main()
{
    // 1 create the sub thread, async
    future<int> fut = async(std::launch::async, worker);

    // 2 wait for the sub thread finish
    fut.wait();

    int result = fut.get();

    cout << "sub thread return " << result << endl;
    
    return 0;
}