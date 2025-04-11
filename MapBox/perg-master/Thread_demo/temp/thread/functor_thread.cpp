#include <iostream>
#include <thread>

class MyFunctor {
public:
    void operator()(int value) const {
        std::cout << "Thread running with value: " << value << std::endl;
    }
};

int main() {
    MyFunctor functor;
    std::thread t(functor, 100); // 直接传对象和参数
    t.join();
    return 0;
}
