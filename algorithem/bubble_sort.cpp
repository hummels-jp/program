#include <iostream>
#include <vector>
using namespace std;


void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break; // Array is already sorted
        }
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Bubble Sort in C++
void bubble_sort_hqq(vector<int>& arr)
{
    int size = arr.size();
    
    // 外层循环
    for (int  i = 0; i < size-1; i++)
    {
        bool swapped = false;
        /* code */
        // 内存循环，最大值会被移动到最后面, 外循环一轮，选出一个最大值
        for (int  j = 0; j < size-i-1; j++)
        {
            // 相邻2个元素互相比较
            if (arr[j] > arr[j + 1])
            {
                /* code */
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
            
        }

        // 如果在上一轮内循环中，没有发生交换，证明未排序数组已经有序，例如： 1，2，3，4，5
        if (swapped == false)
        {
            /* code */
            break;
        }
    }
    
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::cout << "Original array: ";
    printArray(arr);

    // bubbleSort(arr);
    bubble_sort_hqq(arr);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}