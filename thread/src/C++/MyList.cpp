#include <iostream>
using namespace std;
template<class T, int N = 10> class MyList {
    T *data = new T[N];
    int size = 0;
public:
    void push_back(T t) { data[size++] = t; }
    T &operator[](int i) { return data[i]; }
};
