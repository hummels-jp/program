#include <iostream>
#include <mutex>
#include <atomic>

class LazySingleton {
public:
    // Get the singleton instance
    static LazySingleton* getInstance() {
        // First check (no locking)
        LazySingleton* tempInstance = instance.load(std::memory_order_acquire);
        if (!tempInstance) {
            std::lock_guard<std::mutex> lock(instanceMutex);
            // Second check (with locking)
            tempInstance = instance.load(std::memory_order_relaxed);

            // cpu memory barrier to ensure the constructor is complete before storing the pointer
            std::atomic_thread_fence(std::memory_order_acquire); // Ensure the constructor is complete before storing the pointer
            if (!tempInstance) {
                tempInstance = new LazySingleton();
        
                // std::atomic_thread_fence(std::memory_order_release); // Ensure the constructor is complete before storing the pointer
                std::atomic_thread_fence(std::memory_order_release);
                instance.store(tempInstance, std::memory_order_release);
            }
        }
        return tempInstance;
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

    // Static atomic instance pointer
    static std::atomic<LazySingleton*> instance;
    // Mutex for thread safety
    static std::mutex instanceMutex;
};

// Static member variable initialization
std::atomic<LazySingleton*> LazySingleton::instance{nullptr};
std::mutex LazySingleton::instanceMutex;

int main() {
    // Get the singleton instance and call its method
    LazySingleton* singleton1 = LazySingleton::getInstance();
    singleton1->showMessage();

    LazySingleton* singleton2 = LazySingleton::getInstance();
    singleton2->showMessage();

    // Verify that both instances are the same
    if (singleton1 == singleton2) {
        std::cout << "Both instances are the same." << std::endl;
    }

    return 0;
}