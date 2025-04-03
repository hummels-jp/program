#include <iostream>
#include <list>
#include <vector>

template <typename T, template <typename> class Container>
class XCls {
private:
    Container<T> c; // Container with a single template parameter
public:
    void add(const T& value) {
        c.push_back(value);
    }

    void display() const {
        for (const auto& item : c) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
using Lst = std::list<T>; // Alias for std::list

int main() {
    XCls<int, std::vector> myVec; // Using std::vector
    myVec.add(1);
    myVec.add(2);
    myVec.add(3);
    myVec.display();

    XCls<std::string, Lst> myLst; // Using alias for std::list
    myLst.add("Hello");
    myLst.add("World");
    myLst.display();

    return 0;
}
