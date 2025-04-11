#include <iostream>
#include <vector>
#include <algorithm>

// 1. Function pointer predicate: check if a number is even
bool isEven(int n) {
    return n % 2 == 0;
}

// 2. Functor: a callable object that checks if a number is greater than a threshold
class  {
private:
    int threshold;
public:
    IsGreaterThan(int t) : threshold(t) {}
    bool operator()(int n) const {
        return n > threshold;
    }
};

int main() {
    std::vector<int> data = {1, 4, 5, 6, 8, 9, 10};

    // Using lambda expression
    int countLambda = std::count_if(data.begin(), data.end(),
        [](int n) { return n % 2 == 0; }  // Inline predicate to check even numbers
    );

    // Using function pointer
    int countFuncPtr = std::count_if(data.begin(), data.end(), isEven);

    // Using functor object
    IsGreaterThan predicate(5);
    int countFunctor = std::count_if(data.begin(), data.end(), predicate);

    // Print results
    std::cout << "Count using lambda:      " << countLambda << std::endl;
    std::cout << "Count using function pointer: " << countFuncPtr << std::endl;
    std::cout << "Count using functor:     " << countFunctor << std::endl;

    return 0;
}
