#include <iostream>
#include <mutex>

template <typename T>
class SharedPtr {
private:
    T* ptr; // Raw pointer to the managed object
    int* ref_count; // Reference count
    std::mutex* mtx; // Mutex for thread safety

    void release() {
        std::lock_guard<std::mutex> lock(*mtx);
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
            delete mtx;
        }
    }

public:
    // Constructor
    explicit SharedPtr(T* p = nullptr)
        : ptr(p), ref_count(new int(1)), mtx(new std::mutex) {}

    // Copy constructor
    SharedPtr(const SharedPtr& other) {
        std::lock_guard<std::mutex> lock(*other.mtx);
        ptr = other.ptr;
        ref_count = other.ref_count;
        mtx = other.mtx;
        ++(*ref_count);
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count), mtx(other.mtx) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
        other.mtx = nullptr;
    }

    // Copy assignment operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            std::lock_guard<std::mutex> lock(*other.mtx);
            ptr = other.ptr;
            ref_count = other.ref_count;
            mtx = other.mtx;
            ++(*ref_count);
        }
        return *this;
    }

    // Move assignment operator
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            mtx = other.mtx;
            other.ptr = nullptr;
            other.ref_count = nullptr;
            other.mtx = nullptr;
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        if (ref_count) {
            release();
        }
    }

    // Dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the raw pointer
    T* get() const {
        return ptr;
    }

    // Get the reference count
    int use_count() const {
        std::lock_guard<std::mutex> lock(*mtx);
        return *ref_count;
    }
};

// Example usage
int main() {
    SharedPtr<int> sp1(new int(10));
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;

    SharedPtr<int> sp2 = sp1;
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;

    SharedPtr<int> sp3(new int(20));
    sp3 = sp1;
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl;
    std::cout << "sp3 use_count: " << sp3.use_count() << std::endl;

    return 0;
}