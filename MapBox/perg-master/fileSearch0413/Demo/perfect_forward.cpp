#include <iostream>
#include <string>
#include <utility> // For std::forward

class Person {
public:
    // Constructor for lvalue reference
    Person(const std::string& name) : name(name) {
        std::cout << "Lvalue constructor called for: " << name << std::endl;
    }

    // Constructor for rvalue reference
    Person(std::string&& name) : name(std::move(name)) {
        std::cout << "Rvalue constructor called" << std::endl;
    }

    void display() const {
        std::cout << "Person name: " << name << std::endl;
    }

private:
    std::string name;
};

// Factory function using perfect forwarding
template <typename T>
Person make_person(T&& name) {
    return Person(static_cast<T&&>(name));
    // return Person(std::forward<T>(name));
}

int main() {
    std::string name = "John";

    // Call with lvalue
    Person p1 = make_person(name);
    p1.display();

    // Call with rvalue
    Person p2 = make_person(std::string("Doe"));
    p2.display();

    // Call with temporary object
    Person p3 = make_person("Alice");
    p3.display();

    return 0;
}