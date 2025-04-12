#include <future>
#include <iostream>
using namespace std;

int file_find(int a)
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    return a*a;
}

int main()
{
    cout << "async task started " << endl;
    future<int> result = async(file_find, 5);

    cout << "master task continued " << endl;
    int value = result.get();
    cout << "result from async task " << value << endl;

    return 0;
}