#include <iostream>
#include <string>

// Common base class
class Animal {
public:
    Animal(const std::string& name) {
        std::cout << "Animal constructor: " << name << std::endl;
    }
    void speak() const {
        std::cout << "Animal speaking..." << std::endl;
    }
};

// Template derived class
template<typename T>
class Pet : public Animal {
public:
    // Pass name to base class constructor
    Pet(const std::string& name, const T& value) : Animal(name), value_(value) {}

    void showType() const {
        std::cout << "Pet type value: " << value_ << std::endl;
        std::cout << "Type: " << typeid(value_).name() << std::endl;
    }
private:
    T value_;
};

int main() {
    Pet<std::string> dog("DogName", "Dog");
    dog.speak();                // Inherited from Animal
    dog.showType();             // Template member

    Pet<int> cat("CatName", 123);
    cat.speak();
    cat.showType();

    return 0;
}