#include <iostream>
#include <functional>  // for std::bind
#include <algorithm>
#include <vector>

// A simple function
bool isGreater(int a, int b) {
    return a > b;
}

int main() {
    std::vector<int> nums = {1, 5, 3, 7, 4};

    // 1. Bind the second argument to 4: isGreater(x, 4)
    auto greaterThan4 = std::bind(isGreater, std::placeholders::_1, 4);

    // Use in count_if to count numbers greater than 4
    int count = std::count_if(nums.begin(), nums.end(), greaterThan4);

    std::cout << "Numbers greater than 4: " << count << std::endl;

    return 0;
}
