#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* start;       // Pointer to the beginning of the data
    T* end;         // Pointer to the end of the current data
    T* capacity;    // Pointer to the end of the allocated memory

    void reallocate(size_t newCapacity) {
        size_t currentSize = size();
        T* newStart = new T[newCapacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newStart[i] = start[i];
        }
        delete[] start;
        start = newStart;
        end = start + currentSize;
        capacity = start + newCapacity;
    }

public:
    // Constructor
    Vector() : start(nullptr), end(nullptr), capacity(nullptr) {}

    // Destructor
    ~Vector() {
        delete[] start;
    }

    // Add an element to the end
    void push_back(const T& value) {
        if (end == capacity) {
            size_t newCapacity = (capacity - start == 0) ? 1 : (capacity - start) * 2;
            reallocate(newCapacity);
        }
        *end = value;
        ++end;
    }

    // Remove the last element
    void pop_back() {
        if (end > start) {
            --end;
        }
    }

    // Access element by index
    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return start[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return start[index];
    }

    // Get the current size of the vector
    size_t size() const {
        return end - start;
    }

    // Get the current capacity of the vector
    size_t getCapacity() const {
        return capacity - start;
    }

    // Clear the vector
    void clear() {
        end = start;
    }

    // Get iterator to the beginning
    T* begin() {
        return start;
    }

    // Get iterator to the end
    T* endIterator() {
        return end;
    }
};

int main() {
    Vector<int> vec;

    // Add elements
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Access elements
    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Remove an element
    vec.pop_back();

    // Access elements after pop
    std::cout << "After pop_back, vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Display size and capacity
    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Vector capacity: " << vec.getCapacity() << std::endl;

    return 0;
}