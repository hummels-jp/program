#include <iostream>

class Demo {
public:
    // Static member variable
    static int static_value;

    void show() {
        std::cout << "Non-const show()" << std::endl;
        value++;           // OK: can modify non-static member in non-const function
        static_value++;    // OK
        std::cout << " update value in non-const function " << value << std::endl;
        std::cout << " update static value in non-const function " << static_value << std::endl;
    }

    void show() const {
        std::cout << "Const show()" << std::endl;
        // value++; // Error: cannot modify non-static member in const function
        static_value++; // OK: can modify static member in const function
        std::cout << " update static value in const function " << static_value << std::endl;
    }

private:
    int value = 0;
};

int Demo::static_value = 0;

int main() {
    Demo d1;
    const Demo d2;

    d1.show();   // Calls non-const member function, can modify value and static_value
    d2.show();   // Calls const member function, can only modify static_value

    std::cout << "Demo::static_value = " << Demo::static_value << std::endl;

    return 0;
}