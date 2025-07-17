#include <iostream>
using namespace std;

template<typename T>
class MyDeque {
private:
    T* data;
    int cap;
    int front;
    int back;
    int sz;

    void resize(int new_cap) {
        T* new_data = new T[new_cap];
        int j = 0;
        for (int i = 0; i < sz; ++i)
            new_data[i] = (*this)[i];
        delete[] data;
        data = new_data;
        cap = new_cap;
        front = 0;
        back = sz;
    }

public:
    MyDeque(int init_cap = 8)
        : cap(init_cap), front(0), back(0), sz(0) {
        data = new T[cap];
    }

    ~MyDeque() { delete[] data; }

    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    void push_back(const T& val) {
        if (sz == cap) resize(cap * 2);
        data[back] = val;
        back = (back + 1) % cap;
        ++sz;
    }

    void push_front(const T& val) {
        if (sz == cap) resize(cap * 2);
        front = (front - 1 + cap) % cap;
        data[front] = val;
        ++sz;
    }

    void pop_back() {
        if (empty()) return;
        back = (back - 1 + cap) % cap;
        --sz;
    }

    void pop_front() {
        if (empty()) return;
        front = (front + 1) % cap;
        --sz;
    }

    T& operator[](int idx) {
        return data[(front + idx) % cap];
    }
    
    const T& operator[](int idx) const {
        return data[(front + idx) % cap];
    }

    T& front_elem() { return data[front]; }
    T& back_elem() { return data[(back - 1 + cap) % cap]; }
};

int main() {
    MyDeque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);

    cout << "Deque内容: ";
    for (int i = 0; i < dq.size(); ++i)
        cout << dq[i] << " ";
    cout << endl;

    dq.pop_front();
    dq.pop_back();

    cout << "弹出后: ";
    for (int i = 0; i < dq.size(); ++i)
        cout << dq[i] << " ";
    cout << endl;

    return 0;
}