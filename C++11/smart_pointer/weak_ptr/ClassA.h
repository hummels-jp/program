/* --- ClassA.h --- */

/* ------------------------------------------
Author: Huqianqian
Date: 7/4/2025
------------------------------------------ */

#ifndef CLASSA_H
#define CLASSA_H

#include<memory>

using namespace std;
class ClassB;

class ClassA {
public:
    ClassA();
    ~ClassA();

public:
    // shared_ptr<ClassB> ptr_b;
    weak_ptr<ClassB> ptr_b;
};

#endif // CLASSA_H
