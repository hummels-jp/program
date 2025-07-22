#include <type_traits>
#include <iostream>
using namespace std;

void print(int &x)
{
    cout << "print(int &x) " << endl;
}

void print(int &&x)
{
    cout << "print(int &&x)" << endl;
}
template<typename T>
void wrapper(T&& arg)
{
    // print(arg);
    print(std::forward<T>(arg));
}

int main()
{
    int a = 10;
    wrapper(a);

    wrapper(std::move(a));

}

