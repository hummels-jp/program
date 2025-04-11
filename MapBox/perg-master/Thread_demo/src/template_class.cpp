#include "template_class.h"

// TemplateClass constructor implementation
template <typename T>
TemplateClass<T>::TemplateClass(T value) : data(value) {
    std::cout << "TemplateClass constructor called with value: " << data << std::endl;
}

// TemplateClass method implementations
template <typename T>
void TemplateClass<T>::templateMethod(T value) {
    std::cout << "Template method called with value: " << value << std::endl;
}

// Non-template method implementation
template <typename T>
void TemplateClass<T>::nonTemplateMethod() {
    std::cout << "Non-template method called with data: " << data << std::endl;
}

void template_class_demo() {
    // Create an instance of TemplateClass with int type
    TemplateClass<int> intObj(42);
    intObj.templateMethod(100);
    intObj.nonTemplateMethod();

    // Create an instance of TemplateClass with double type
    TemplateClass<double> doubleObj(3.14);
    doubleObj.templateMethod(2.71);
    doubleObj.nonTemplateMethod();
}
