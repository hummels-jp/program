#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Foo {
    Foo(int x) : val(x) { cout << "Foo(" << val << ")\n"; }
    int val;
};

int main() {
    vector<unique_ptr<Foo>> vec;

    // 使用 push_back，需要 std::move
    unique_ptr<Foo> p1 = make_unique<Foo>(1);
    vec.push_back(std::move(p1));

    // 使用 emplace_back，直接构造
    vec.emplace_back(make_unique<Foo>(2));

    // 也可以直接 emplace_back 构造对象
    vec.emplace_back(new Foo(3));

    for (auto& ptr : vec) {
        cout << ptr->val << endl;
    }
    return 0;
}