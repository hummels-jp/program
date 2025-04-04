#include <iostream>
#include <vector>
// 希尔排序的实现
// Shell Sort Implementation in C++
// 希尔排序的实现
void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    // Start with a large gap, then reduce the gap
    // 从一个较大的间隔开始，然后逐渐减小间隔
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // 对于这个间隔大小进行插入排序       
        for (int i = gap; i < n; i++) {
            // Add arr[i] to the elements that have been gap sorted
            // 使 arr[i] 成为已经间隔排序的元素
            // Save arr[i] in temp and make a hole at position i
            // 将 arr[i] 保存到临时变量中，并在位置 i 上留一个空位
            // 使 arr[i] 成为已经间隔排序的元素

            int temp = arr[i];
            int j;
            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            // 在找到 arr[i] 的正确位置之前，将早期的间隔排序元素向上移动
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {12, 34, 54, 2, 3};
    std::cout << "Original array: ";
    printArray(arr);

    shellSort(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}