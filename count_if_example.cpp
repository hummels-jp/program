#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 使用 count_if 统计偶数的数量
    int evenCount = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0; // 条件：是偶数
    });

    std::cout << "Number of even numbers: " << evenCount << std::endl;

    // 使用 count_if 和 lambda 表达式统计非偶数的数量
    int oddCount = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 != 0; // 条件：是奇数
    });

    // 使用 not1 和 std::not1 示例
    int greaterThanFiveCount = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5; // 条件：大于5
    });
    std::cout << "Number of numbers greater than 5: " << greaterThanFiveCount << std::endl;
    std::cout << "Number of odd numbers: " << oddCount << std::endl;

    return 0;
}
