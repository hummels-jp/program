#include <iostream>
using namespace std;

// 定义命名空间
namespace myspace {
    int value = 42;
    void print() {
        cout << "myspace::value = " << value << endl;
    }
}

// 嵌套命名空间
namespace outer {
    namespace inner {
        void hello() {
            cout << "Hello from outer::inner" << endl;
        }
    }
}

// unnamed namespace
namespace {
    int onlyInThisFile = 123;
    void onlyHere() {
        cout << "onlyInThisFile: " << onlyInThisFile << endl;
    }
}

int main() {
    // 使用命名空间中的成员
    myspace::print();
    cout << myspace::value << endl;

    // 使用嵌套命名空间
    outer::inner::hello();

    // 使用 using 声明
    using myspace::value;
    cout << "using value: " << value << endl;

    // 使用 using namespace（不推荐在头文件中使用）
    using namespace myspace;
    print();

    onlyHere();

    return 0;
}