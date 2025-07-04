/* --- ClassB.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 7/4/2025
------------------------------------------ */

#ifndef CLASSB_H
#define CLASSB_H


#include <memory>
using namespace std;

class ClassA;

class ClassB {
public:
    ClassB();
    ~ClassB();

public:
    // shared_ptr<ClassA> ptr_a;
    weak_ptr<ClassA> ptr_a;
};

#endif // CLASSB_H
