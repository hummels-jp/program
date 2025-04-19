#include <iostream>
#include <mutex>

class HungrySingleton {
public:
    // Get the singleton instance
    static HungrySingleton& getInstance() {
        return instance;
    }

    // Disable copy constructor and assignment operator
    HungrySingleton(const HungrySingleton&) = delete;
    HungrySingleton& operator=(const HungrySingleton&) = delete;

    // Example method
    void showMessage() const {
        std::cout << "Hungry Singleton Instance Address: " << this << std::endl;
    }

private:
    // Private constructor
    HungrySingleton() {
        std::cout << "HungrySingleton Constructor Called" << std::endl;
    }

    // Static instance, initialized directly at program startup
    static HungrySingleton instance;
};

// Static member variable initialization
HungrySingleton HungrySingleton::instance;

int main() {
    // Get the singleton instance and call its method
    HungrySingleton& singleton1 = HungrySingleton::getInstance();
    singleton1.showMessage();

    HungrySingleton& singleton2 = HungrySingleton::getInstance();
    singleton2.showMessage();

    // Verify that both instances are the same
    if (&singleton1 == &singleton2) {
        std::cout << "Both instances are the same." << std::endl;
    }

    return 0;
}