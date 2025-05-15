#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>
class Vector
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<T> initialized" << endl;
        cout << typeid(T).name() << endl;
    }
};


// Specialization for const char* type, full specialization
template <>
class Vector<const char*>
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<const char*> initialized" << endl;
        cout << typeid(const char*).name() << endl;
    }
};


template <>
class Vector<int>
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<int> initialized" << endl;
        cout << typeid(int).name() << endl;
    }
};

// Specialization for T* type, partial specialization
template <typename T>
class Vector<T*>
{   
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<T*> initialized" << endl;
        cout << typeid(T*).name() << endl;
    }
};

// Specialization for T(*) (int, int) type, full specialization
template <>
class Vector<int(*) (int, int)>
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<int(*) (int, int)> initialized" << endl;
        cout << typeid(int(*) (int, int)).name() << endl;
    }
};

// Specialization for T(*) (...Args) type, partial specialization
template <typename R, typename... Args>
class Vector<R(*)(Args...)>
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<R(*)(Args...)> initialized" << endl;
        cout << typeid(R(*)(Args...)).name() << endl;
    }
};

// function pointer, Specialization for T(*) (T1, T2) type, partial specialization
template <typename R, typename T1, typename T2>
class Vector<R(*)(T1, T2)>
{   
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<R(*)(T1, T2)> initialized" << endl;
        cout << typeid(R(*)(T1, T2)).name() << endl;
    }
};

// function object, partial specialization
template <typename R, typename T1, typename T2, typename T3>
class Vector<R(T1, T2, T3)>
{
public:
    Vector() {
        // Constructor implementation
        cout << "class template Vector<R(T1, T2, T3) initialized" << endl;
        cout << typeid(R(*)(T1, T2, T3)).name() << endl;
    }
};


int main()
{
    Vector<int> v1; // OK: T is int
    Vector<double> v2; // OK: T is double
    Vector<const char*> v3; // OK: T is const char*
    Vector<char*> v4; // OK: T is char*
    Vector<float*> v5; // OK: T is float*
    //  function pointer
    // Vector<int(*) (int, int)> v6; // Error: T is int(*) (int, int)
    Vector<int(*)(int, int)> v6; // OK: T is int*
    Vector<double(*)(double, double)> v7; // OK: T is int*
    Vector<double(*)(double, double, double)> v8; // OK: T is int*

    // function object
    Vector<int(int, int)> v9; // OK: T is int
    Vector<double(double, double, double)> v10; // OK: T is int


    return 0;
}