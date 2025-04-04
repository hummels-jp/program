#include <iostream>
#include <vector>

// Insertion Sort in C++
// This program sorts an array using the insertion sort algorithm.  
// The insertion sort algorithm builds a sorted array one element at a time.
// It is much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, or merge sort.
// The algorithm is adaptive, i.e., it is efficient for data sets that are already substantially sorted: the time complexity is O(n) in the best case (when the array is already sorted).
// The worst-case time complexity is O(n^2), and the average-case time complexity is O(n^2).
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    // Traverse through 1 to n
    // Traverse through 1 to n (the first element is already sorted)
    for (int i = 1; i < n; ++i) {
        // 拿出无序队列的第一个元素
        int key = arr[i];

        // 设置内存循环的起始值 = 有序序列的最后一个元素
        int j = i - 1;

        // 将有序序列的值与临时变量进行比较，进行后移
        while (j >= 0 && arr[j] > key) {
            // Move the element to the right
            arr[j + 1] = arr[j];
            // 从后往前进行比较
            --j;
        }
        // 将临时变量插入到有序序列中
        arr[j + 1] = key;
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6};
    std::cout << "Original array: ";
    printArray(arr);

    insertionSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}