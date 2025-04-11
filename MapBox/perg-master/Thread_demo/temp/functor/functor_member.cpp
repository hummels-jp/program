#include <iostream>

class RangeChecker {
private:
    int lower;
    int upper;

public:
    // Constructor
    RangeChecker(int l, int u) : lower(l), upper(u) {}

    // Functor functionality: Check if a value is within the range
    bool operator()(int value) const {
        return value >= lower && value <= upper;
    }

    // Member method: Modify the range
    void setRange(int l, int u) {
        lower = l;
        upper = u;
    }

    void printRange() const {
        std::cout << "Current range is [" << lower << ", " << upper << "]" << std::endl;
    }
};

/*
operator() implements the functor functionality;

setRange() is a custom member function to dynamically modify the state;

Member variables lower and upper represent the "state" of the callable object;

It can be flexibly used with standard algorithms such as std::count_if, std::find_if, etc.
*/
int main() {
    RangeChecker checker(10, 20);  // Create a functor object with an initial range of [10, 20]

    checker.printRange();

    std::cout << "Is 15 within the range? " << std::boolalpha << checker(15) << std::endl;
    std::cout << "Is 25 within the range? " << std::boolalpha << checker(25) << std::endl;

    checker.setRange(5, 8);  // Modify the range
    checker.printRange();
    std::cout << "Is 7 within the range? " << std::boolalpha << checker(7) << std::endl;

    return 0;
}
