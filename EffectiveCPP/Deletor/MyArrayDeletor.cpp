#include <memory>
#include <iostream>
using namespace std;


void int_array_deletor(int* p)
{
    cout << "int_array_deletor " << endl;
    delete [] p;
}

struct MyArrayDeletor
{
    /* data */
    void operator()(int*p)
    {
        cout << "MyArrayDeletor " << endl;
        delete[] p;
    }
};



int main()
{
    int* p = new int[10];

    // shared_ptr<int> sp1(p, int_array_deletor);

    shared_ptr<int> sp2(p, MyArrayDeletor{});
}
