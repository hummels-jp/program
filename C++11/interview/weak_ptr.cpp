#include <iostream>
#include <memory>
#include <thread>
using namespace std;

struct Foo {
    void print() { cout << "Foo::print()" << endl; }
};

void threadFunc(weak_ptr<Foo> wp) {
    if (auto sp = wp.lock()) { // 尝试提升为 shared_ptr
        sp->print();           // 只有对象存活时才调用
    } else {
        cout << "Foo expired" << endl;
    }
}

int main() {
    auto sp = make_shared<Foo>();
    thread t(threadFunc, weak_ptr<Foo>(sp));
    t.join();

    // 如果对象已析构，子线程不会调用 print
    return 0;
}