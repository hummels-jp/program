#include <iostream>
#include <vector>
#include <stdexcept>

// Template class Stack
template<typename T>
class Stack {
private:
    std::vector<T> elems; // Container to store stack elements
public:
    // Push an element onto the stack
    void push(const T& value) {
        elems.push_back(value);
    }

    // Pop the top element from the stack
    void pop() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elems.pop_back();
    }

    // Access the top element
    T& top() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elems.back();
    }

    // Check if the stack is empty
    bool empty() const {
        return elems.empty();
    }

    // Get the size of the stack
    size_t size() const {
        return elems.size();
    }
};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Stack top: " << s.top() << std::endl;
    s.pop();
    std::cout << "Stack top after pop: " << s.top() << std::endl;

    while (!s.empty()) {
        std::cout << "Popping: " << s.top() << std::endl;
        s.pop();
    }

    return 0;
}