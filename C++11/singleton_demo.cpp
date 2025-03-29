#include <iostream>
using namespace std;

class A
{
    private:
        static A* instance; // Static pointer to hold the single instance of the class
        A() {} // Private constructor to prevent direct instantiation
        A(const A& other){} // Private copy constructor to prevent copying

    public:
        // Static method to provide access to the single instance
        static A* getInstance()
        {
            if (instance == nullptr) // Create the instance if it doesn't exist
            {
                instance = new A();
            }
            return instance; // Return the single instance
        }

        // Example method to demonstrate functionality
        void say_hello()
        {
            std::cout << "hello" << std::endl;
        }
};

// Initialize the static member
A* A::instance = nullptr;

int main()
{
    // Access the Singleton instance and call its method
    A* a = A::getInstance();
    a->say_hello();

    // Access the Singleton instance again and call its method
    A* b = A::getInstance();
    b->say_hello();

    // Both 'a' and 'b' point to the same instance
    return 0;
}