#include <iostream>
#include <vector>
#include <functional> // for std::mem_fn
#include <algorithm>

class Person {
public:
    Person(std::string name) : name(name) {}

    void sayHello() const {
        std::cout << "Hello, I'm " << name << std::endl;
    }

private:
    std::string name;
};

int main() {
    std::vector<Person> people = {
        Person("Alice"),
        Person("Bob"),
        Person("Charlie")
    };

    // Use std::mem_fn to adapt the member function for for_each
    std::for_each(people.begin(), people.end(), std::mem_fn(&Person::sayHello));

    return 0;
}
