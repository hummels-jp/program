#include <iostream>
#include <cstdlib> // for malloc, free

int main() {
    // 使用 new 分配单个int
    int* p1 = new int(10);
    std::cout << "p1: " << *p1 << std::endl;
    delete p1; // 释放new分配的内存

    // 使用 new 分配数组
    int* arr = new int[5]{1,2,3,4,5};
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    delete[] arr; // 释放new[]分配的数组

    // 使用 malloc 分配内存
    int* p2 = (int*)malloc(sizeof(int));
    if (p2) {
        *p2 = 20;
        std::cout << "p2: " << *p2 << std::endl;
        free(p2); // 释放malloc分配的内存
    }

    // 使用 malloc 分配数组
    int* arr2 = (int*)malloc(5 * sizeof(int));
    if (arr2) {
        for (int i = 0; i < 5; ++i) 
            arr2[i] = i + 10;
        for (int i = 0; i < 5; ++i) {
            std::cout << "arr2[" << i << "] = " << arr2[i] << std::endl;
        }
        free(arr2); // 释放malloc分配的内存
    }

    return 0;
}