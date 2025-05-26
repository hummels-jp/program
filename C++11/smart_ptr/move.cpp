#include <iostream>
#include <string>
#include <utility> // for std::move

void printAndClear(std::string&& str) {
    std::cout << "String content: " << str << std::endl;
    str.clear();
}

#include <vector>

// 传递右值引用的函数
void printVectorAndClear(std::vector<int>&& vec) {
    std::cout << "Vector content: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    vec.clear();
}

// 传递左值引用的函数
void copyVector(const std::vector<int>& vec) {
    std::vector<int> copiedVec = vec; // 复制 vector
    std::cout << "Copied Vector content: ";
    for (const auto& elem : copiedVec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// 使用左值传递的函数
void modifyVector(std::vector<int> vec) {
    vec.push_back(42); // 修改副本
    std::cout << "Modified Vector content inside function: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string original = "Hello, World!";
    
    // 使用 std::move 将 original 转换为右值引用
    printAndClear(std::move(original));
    
    // original 现在是空的
    std::cout << "Original after move: " << original << std::endl;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    printVectorAndClear(std::move(vec)); // 传递右值引用
    // vec 现在是空的   
    std::cout << "Vector after move: ";
    for (const auto& elem : vec) {
        std::cout << elem << " "; // 输出空的 vector
    }
    std::cout << std::endl;
    std::cout << "Vector size after move: " << vec.size() << std::endl; // 输出 0
    std::cout << "Vector capacity after move: " << vec.capacity() << std::endl; // 输出 0   

    // 传递左值引用
    std::vector<int> vec2 = {6, 7, 8, 9, 10};   
    copyVector(vec2); // 传递左值引用
    std::cout << "Vector2 after copy: ";
    for (const auto& elem : vec2) {
        std::cout << elem << " "; // 输出原始 vector
    }
    std::cout << std::endl;
    std::cout << "Vector2 size after copy: " << vec2.size() << std::endl; // 输出 5
    std::cout << "Vector2 capacity after copy: " << vec2.capacity() << std::endl; // 输出 5

    // 使用左值传递的函数
    std::vector<int> vec3 = {11, 12, 13, 14, 15};   
    modifyVector(vec3); // 传递左值引用
    std::cout << "Vector3 after modify: ";
    for (const auto& elem : vec3) {
        std::cout << elem << " "; // 输出原始 vector
    }
    std::cout << std::endl;
    std::cout << "Vector3 size after modify: " << vec3.size() << std::endl; // 输出 5
    std::cout << "Vector3 capacity after modify: " << vec3.capacity() << std::endl; // 输出 5
    std::cout << "Vector3 content after modify: ";  
    for (const auto& elem : vec3) {
        std::cout << elem << " "; // 输出原始 vector
    }
    std::cout << std::endl;



    return 0;
}