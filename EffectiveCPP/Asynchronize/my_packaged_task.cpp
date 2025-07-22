#include <future>
#include <iostream>
using namespace std;

int multiple(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(1));
    return a*b;
}

int main()
{
    packaged_task<int(int, int)> task(multiple);
    future<int> _future = task.get_future();

    thread t1(std::move(task), 3, 4);

    cout << "main thread is free to do other things" << endl;
    int result = _future.get();
    cout << "sub thread result is " << result << endl;

    t1.join();

    return 0;
}