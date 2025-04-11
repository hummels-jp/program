#include <iostream>
#include <string>
#include "template_class_object_parameter.h" // Custom header for template class object parameter

// 定义模板类
template <typename T>
class MyTemplateClass {
public:
    MyTemplateClass(T value) : data(value) {}
    void display() const {
        std::cout << "Value: " << data << std::endl;
    }
    T getData() const {
        return data;
    }

private:
    T data;
};

// 定义一个全局函数，使用模板类对象，将参数模板化
template <typename T, typename U>
void processTwoTemplateObjects(const MyTemplateClass<T>& obj1, const MyTemplateClass<U>& obj2) {
    std::cout << "Processing two objects:" << std::endl;
    std::cout << "Object 1 data: " << obj1.getData() << std::endl;
    std::cout << "Object 2 data: " << obj2.getData() << std::endl;
}

// 定义全局函数，使用模板类对象作为输入参数
template <typename T>
void processTemplateObject(const MyTemplateClass<T>& obj) {
    std::cout << "Processing object with data: " << obj.getData() << std::endl;
}

int template_class_object_parameter_demo() {
    MyTemplateClass<int> intObj(42);
    MyTemplateClass<std::string> stringObj("Hello, Template!");

    processTemplateObject(intObj);
    processTemplateObject(stringObj);

    processTwoTemplateObjects(intObj, stringObj);
    processTwoTemplateObjects(stringObj, intObj);


    return 0;
}