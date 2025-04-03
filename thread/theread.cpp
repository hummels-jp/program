#include <iostream>
#include <thread>
using namespace std;
using namespace std::this_thread;

void printHello() {
    std::cout << "Hello, World from thread!" << std::endl;
}

void increment(int& value) {
    value++;
}
void displayThreadId() {
    std::cout << "Current thread ID: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t(printHello);
    t.join(); // Wait for the thread to finish

    int a = 2;
    std::thread t2(increment, std::ref(a)); // Pass by reference using std::ref
    t2.join(); // Wait for the thread to finish
    cout << "Value of a after increment: " << a << std::endl;

    std::thread t3(displayThreadId); // Create a thread to display the thread ID
    t3.join(); // Wait for the thread to finish 

    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;

    return 0;
}