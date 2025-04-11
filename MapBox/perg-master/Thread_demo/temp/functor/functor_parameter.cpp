#include <iostream>
#include <vector>
#include <algorithm>

// 仿函数：判断一个数字是否是偶数
class IsEven {
public:
    bool operator()(int value) const {
        return value % 2 == 0;
    }
};

class IsOdd{
public:
    bool operator()(int value) const{
        return value%2 ==1;
    }
};

// 函数：接收一个仿函数作为参数
template <typename Func>
void filterAndPrint(const std::vector<int>& data, Func predicate) {
    for (int val : data) {
        if (predicate(val)) {  // 使用仿函数判断
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};

    std::cout << "Even data: ";
    filterAndPrint(nums, IsEven());  // 传入仿函数对象

    std::cout << "odd number: ";
    filterAndPrint(nums, IsOdd());

    return 0;
}
