
#include "ClassA.h"
#include "ClassB.h"


#include <memory>
#include <iostream>
using namespace std;

int main()
{
    shared_ptr<ClassA> a = make_shared<ClassA>();
    shared_ptr<ClassB> b = make_shared<ClassB>();

    a->ptr_b = b;
    b->ptr_a = a;

}