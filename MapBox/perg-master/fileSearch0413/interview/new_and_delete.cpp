#include <iostream>
#include <string>

class MyClass {
private:
    std::string name;

public:
    MyClass(const std::string& name) : name(name) {
        std::cout << "Constructor called for " << name << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called for " << name << std::endl;
    }

    void display() const {
        std::cout << "Hello, I am " << name << std::endl;
    }
};

int main() {
    // Using new to create a single object
    MyClass* obj = new MyClass("SingleObject");
    obj->display();

    // Deleting the object
    delete obj;

    // Using new to create an array of objects
    MyClass* objArray = new MyClass[3]{
        MyClass("Object1"),
        MyClass("Object2"),
        MyClass("Object3")
    };

    // Accessing array elements
    for (int i = 0; i < 3; ++i) {
        objArray[i].display();
    }

    // Deleting the array of objects
    delete[] objArray;

    return 0;
}