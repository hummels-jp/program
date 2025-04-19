#include <iostream>
#include <mutex>

class LazySingleton {
public:
    // Get the singleton instance
    static LazySingleton& getInstance() {
        std::call_once(initInstanceFlag, []() {
            instance = new LazySingleton();
        });
        return *instance;
    }

    // Disable copy constructor and assignment operator
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

    // Example method
    void showMessage() const {
        std::cout << "Lazy Singleton Instance Address: " << this << std::endl;
    }

private:
    // Private constructor
    LazySingleton() {
        std::cout << "LazySingleton Constructor Called" << std::endl;
    }

    // Private destructor
    ~LazySingleton() {
        std::cout << "LazySingleton Destructor Called" << std::endl;
    }

    // Static instance pointer
    static LazySingleton* instance;
    // Flag for std::call_once
    static std::once_flag initInstanceFlag;
};

// Static member variable initialization
LazySingleton* LazySingleton::instance = nullptr;
std::once_flag LazySingleton::initInstanceFlag;

int main() {
    // Get the singleton instance and call its method
    LazySingleton& singleton1 = LazySingleton::getInstance();
    singleton1.showMessage();

    LazySingleton& singleton2 = LazySingleton::getInstance();
    singleton2.showMessage();

    // Verify that both instances are the same
    if (&singleton1 == &singleton2) {
        std::cout << "Both instances are the same." << std::endl;
    }

    return 0;
}