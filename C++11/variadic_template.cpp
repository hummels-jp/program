#include <iostream>
using namespace std;
void print() {}

template<typename T, typename... Args>
void print(const T& firstArg, const Args&... args)
{
    std::cout << firstArg << std::endl;
    print(args...);
}

int main()
{
    print(1, "Hello", 2.5, 'c');
    return 0;
}