// template_class.h
#ifndef TEMPLATE_CLASS_H
#define TEMPLATE_CLASS_H

#include <iostream>

template <typename T>
class TemplateClass {
public:
    TemplateClass(T value);
    void templateMethod(T value);
    void nonTemplateMethod();

private:
    T data;
};

void template_class_demo();

#endif // TEMPLATE_CLASS_H