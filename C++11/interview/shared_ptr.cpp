#include <iostream>
#include <memory>
using namespace std;

struct Node {
    int val;
    shared_ptr<Node> next;      // 强引用
    weak_ptr<Node> prev;        // 弱引用，避免循环引用
    Node(int v) : val(v) {}
};

int main() {
    auto n1 = make_shared<Node>(1);
    auto n2 = make_shared<Node>(2);

    n1->next = n2;
    n2->prev = n1; // 交叉引用，prev用weak_ptr避免循环引用

    // 将弱智能指针提升为强智能指针
    if (auto sp = n2->prev.lock()) {
        cout << "prev value: " << sp->val << endl;
    } else {
        cout << "prev expired" << endl;
    }

    return 0;
}