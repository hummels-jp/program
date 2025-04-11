#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

bool isOdd(int x) { return x % 2 != 0; }

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Negate the predicate: find even numbers
    auto isEven = std::not_fn(isOdd);

    int count = std::count_if(nums.begin(), nums.end(), isEven);
    std::cout << "Even count: " << count << std::endl;

    return 0;
}
