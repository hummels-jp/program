#include <iostream>
using namespace std;
#include "friend_in_template_class.h"

// Forward declaration of the template class
// template <typename T>
// class MyClass;

// Forward declaration of the friend function defined outside the class
// template <typename T>
// void displayValue(const MyClass<T>& obj);

template <typename T>
class MyClass {
private:
    T value;

public:
    MyClass(T val) : value(val) {}

    // Friend function defined inside the class
    friend void showValue(const MyClass& obj) {
        cout << "Value (inside): " << obj.value << endl;
    }

    // Declare a friend function defined outside the class
    // friend void displayValue(const MyClass& obj);
};

// Friend function defined outside the class
template <typename T>
void displayValue(const MyClass<T>& obj) {
    cout << "Value (outside): " << obj.value << endl;
}

int friend_in_template_class_demo() {
    MyClass<int> obj(42);

    showValue(obj);       // Call the friend function defined inside the class
    // displayValue(obj);    // Call the friend function defined outside the class

    return 0;
}