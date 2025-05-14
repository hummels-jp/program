#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

bool greater_than(int a, int b) {
    return a > b;
}

int main() {
    std::vector<int> v{1, 5, 3, 7, 2, 8};

    // C++11 推荐用 std::bind 替代 bind1st
    auto gt_5 = std::bind(greater_than, std::placeholders::_1, 5);

    std::cout << "大于5的元素有：";
    for (int x : v) {
        if (gt_5(x)) {
            std::cout << x << " ";
        }
    }
    std::cout << std::endl;

    // 也可以用于算法
    int count = std::count_if(v.begin(), v.end(), gt_5);
    std::cout << "大于5的元素个数: " << count << std::endl;

    return 0;
}