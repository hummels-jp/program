#include <iostream>
#include <memory>
#include <typeinfo>

class Base {
public:
    virtual ~Base() = default; // Virtual destructor for polymorphism
    virtual void show() const {
        std::cout << "Base class show()" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() const override {
        std::cout << "Derived class show()" << std::endl;
    }

    void derivedOnlyFunction() const {
        std::cout << "Derived class specific function" << std::endl;
    }
};

int main() {
    // Static cast example
    std::cout << "Static cast example:" << std::endl;
    Base* basePtr = new Derived(); // Base pointer pointing to Derived object
    Derived* derivedPtr = static_cast<Derived*>(basePtr); // Safe because basePtr actually points to a Derived object
    derivedPtr->show();
    derivedPtr->derivedOnlyFunction();

    // Dynamic cast example
    std::cout << "\nDynamic cast example:" << std::endl;
    Base* basePtr2 = new Base(); // Base pointer pointing to a Base object
    Derived* derivedPtr2 = dynamic_cast<Derived*>(basePtr2); // Unsafe, basePtr2 does not point to a Derived object
    if (derivedPtr2) {
        derivedPtr2->show();
    } else {
        std::cout << "dynamic_cast failed: basePtr2 is not pointing to a Derived object" << std::endl;
    }

    // Static cast with references
    std::cout << "\nStatic cast with references:" << std::endl;
    Derived derivedObj;
    Base& baseRef = derivedObj; // Base reference to Derived object
    Derived& derivedRef = static_cast<Derived&>(baseRef); // Safe because baseRef refers to a Derived object
    derivedRef.show();
    derivedRef.derivedOnlyFunction();

    // Dynamic cast with references
    std::cout << "\nDynamic cast with references:" << std::endl;
    Base baseObj;
    Base& baseRef2 = baseObj; // Base reference to Base object
    try {
        Derived& derivedRef2 = dynamic_cast<Derived&>(baseRef2); // Unsafe, baseRef2 does not refer to a Derived object
        derivedRef2.show();
    } catch (const std::bad_cast& e) {
        std::cout << "dynamic_cast failed: " << e.what() << std::endl;
    }

    // Clean up
    delete basePtr;
    delete basePtr2;

    return 0;
}