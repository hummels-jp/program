/* --- ClassB.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 7/4/2025
------------------------------------------ */

#ifndef CLASSB_H
#define CLASSB_H

#include "ClassA.h"
#include <memory>
using namespace std;

class ClassB {
public:
    ClassB();
    ~ClassB();

private:
    shared_ptr<ClassA> ptr_a;
};

#endif // CLASSB_H
