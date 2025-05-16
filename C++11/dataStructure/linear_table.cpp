#include <iostream>

class LinearTable {
public:
    LinearTable(int capacity = 100) : size_(0), capacity_(capacity) {
        data_ = new int[capacity_];
    }

    ~LinearTable() {
        delete[] data_;
    }

    bool insert(int value) {
        if (size_ >= capacity_) {
            resize(capacity_ * 2); // 自动扩容
        }
        data_[size_++] = value;
        return true;
    }

    bool remove(int index) {
        if (index < 0 || index >= size_) return false;
        for (int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        return true;
    }

    int get(int index) const {
        if (index < 0 || index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

    void print() const {
        for (int i = 0; i < size_; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

    // 支持手动调整容量
    void resize(int new_capacity) {
        if (new_capacity <= capacity_) return;
        int* new_data = new int[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    int* data_;
    int size_;
    int capacity_;
};

int main() {
    LinearTable linetable(2);
    linetable.insert(10);
    linetable.insert(20);
    linetable.print(); // 输出: 10 20

    linetable.insert(30); // 触发扩容
    linetable.print(); // 输出: 10 20 30

    linetable.remove(1);
    linetable.print(); // 输出: 10 30

    std::cout << "Element at index 1: " << linetable.get(1) << std::endl; // 输出: 30
    std::cout << "Current capacity: " << linetable.capacity() << std::endl;

    // 手动扩容
    linetable.resize(100);
    std::cout << "Capacity after manual resize: " << linetable.capacity() << std::endl;

    return 0;
}