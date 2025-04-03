#include <iostream>
#include <list>
#include <algorithm> // 用于 std::sort
#include <chrono>    // 用于计时
#include <random>    // 用于生成随机数

const int NUM_ELEMENTS = 1000000; // 元素数量

int main() {
    // 定义一个随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    // 定义一个 std::list
    std::list<int> lst;

    lst.max_size(); // 触发 max_size() 的计算
    std::cout << "Max size of list: " << lst.max_size() << std::endl;

    // 填充 list 并计时
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        lst.push_back(dis(gen)); // 填充随机数
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 排序 list 并计时, 使用 list 的成员函数 sort
    start = std::chrono::high_resolution_clock::now();
    lst.sort(); // 使用 list 的成员函数 sort
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to sort the list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
    
    // 注意：std::list 没有提供 std::sort 函数，必须使用 list 的成员函数 sort
    // 如果需要使用 std::sort，需要将 list 转换为 vector 或 array   
    // 使用 std::sort 对 list 进行排序
    // 需要先将 list 转换为 vector
    std::vector<int> vec(lst.begin(), lst.end());

    start = std::chrono::high_resolution_clock::now();
    std::sort(vec.begin(), vec.end());
    end = std::chrono::high_resolution_clock::now();

    // 将排序后的 vector 复制回 list
    lst.assign(vec.begin(), vec.end());

    std::cout << "Time taken to sort the list using std::sort: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 遍历 list 并计时
    start = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& val : lst) {
        sum += val; // 模拟访问操作
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to traverse the list: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    // 输出总和（防止优化）
    std::cout << "Sum of elements: " << sum << std::endl;

    return 0;
}