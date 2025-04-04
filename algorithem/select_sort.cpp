#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// 选择排序算法的实现
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) 
        // Find the index of the minimum element in the unsorted part of the array
        // 在未排序部分中找到最小元素的索引
        {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        // 将找到的最小元素与未排序部分的第一个元素交换
        std::swap(arr[i], arr[minIndex]);
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void select_sort_hqq(vector<int>& arr)
{
    int size = arr.size();
    // 外循环，前面的数是有序数组，最后一个值为最大值
    for (int  i = 0; i < size-1; i++)
    {
        /* code */
        int min_index = i;
        // 内循环，顺序与最大值进行比较，如果小于最大值，则交换
        for (int j = i+1; j < size; j++)
        {
            /* code */
            if(arr[min_index] > arr[j])
            {
                min_index = j;
            }
        }

        // 内循环完毕，找出此轮的最小值
        if (min_index !=i)
        {
            /* code */
            swap(arr[min_index], arr[i]);
        }        

    }
    
}

int main() {
    std::vector<int> arr = {64, 25, 12, 22, 11};
    std::cout << "Original array: ";
    printArray(arr);

    // selectionSort(arr);
    select_sort_hqq(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}