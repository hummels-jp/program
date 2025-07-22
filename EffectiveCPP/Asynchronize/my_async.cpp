#include <future>
#include <iostream>
using namespace std;

int add(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));
    return a + b;
}

int main()
{
    future<int> _future = async(launch::async, add, 3, 4);
    cout << "Main thread is free to do other work..." << endl;

    int result = _future.get();
    cout << "async result is "  << result << endl;
    return 0;
}