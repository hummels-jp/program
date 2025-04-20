#include <iostream>
#include <memory>
#include <exception>

class Person {
public:
    Person() {
        std::cout << "Person constructor called" << std::endl;
    }
    ~Person() {
        std::cout << "Person destructor called" << std::endl;
    }
};

void do_logic(std::shared_ptr<Person> sp, int number) {
    std::cout << "do_logic called with number: " << number << std::endl;
}

int get_number() {
    std::cout << "get_number" << std::endl;
    throw std::exception(); // Simulate an exception
    return 100;
}

int main() {
    try {
        // 1. Constructor function - Exception unsafe
        // do_logic(std::shared_ptr<Person>(new Person), get_number());

        // // 2. make_shared - Exception safe
        do_logic(std::make_shared<Person>(), get_number());
    } catch (...) {
        std::cout << "Error handling..." << std::endl;
    }

    return 0;
}