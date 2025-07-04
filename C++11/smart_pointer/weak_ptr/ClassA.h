/* --- ClassA.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 7/4/2025
------------------------------------------ */

#ifndef CLASSA_H
#define CLASSA_H

#include<memory>
#include "ClassB.h"
using namespace std;

class ClassA {
public:
    ClassA();
    ~ClassA();

private:
    shared_ptr<ClassB> ptr_b;
};

#endif // CLASSA_H
