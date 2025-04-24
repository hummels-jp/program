#include <iostream>
#include <future>
#include <thread>
#include <functional>

int add(int x, int y) {
    return x + y;
}

int main()
{
    auto future1 = std::async(std::launch::async, add, 10, 20);
    std::cout << "Result from add: " << future1.get() << std::endl;

    
}