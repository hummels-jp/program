#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : value(value) {
        std::cout << "MyClass constructor called with value: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor called for value: " << value << std::endl;
    }

private:
    int value;
};

int main() {
    std::cout << "Using std::shared_ptr with new:" << std::endl;
    {
        // 使用 std::shared_ptr 和 new
        std::shared_ptr<MyClass> ptr1(new MyClass(10));
        std::cout << "Shared pointer created using new." << std::endl;
    } // ptr1 超出作用域，释放资源

    std::cout << "\nUsing std::make_shared:" << std::endl;
    {
        // 使用 std::make_shared
        std::shared_ptr<MyClass> ptr2 = std::make_shared<MyClass>(20);
        std::cout << "Shared pointer created using make_shared." << std::endl;
    } // ptr2 超出作用域，释放资源

    return 0;
}