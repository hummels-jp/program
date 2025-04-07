#include <iostream>
#include <vector>
using namespace std;

void merge(std::vector<int>& arr, int left, int mid, int right) {
    // Create temporary arrays for left and right subarrays
    int n1 = mid - left + 1;    // Size of left subarray
    int n2 = right - mid;     // Size of right subarray

    // Create temporary arrays
    std::vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    
    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into arr[left..right]
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


void merge_sorted_array_hqq(vector<int>& arr, int left, int right, vector<int>& temp)
{
    int mid = left + (right - left) / 2;
    
    // 定义2个指针，分别指向左子列，右子列的第一个元素。 左，右子列是有序列表
    int i = left;
    int j = mid + 1;
    // 合并后的数据存储在 temp 中
    int index = 0;
    while (i <=mid && j <=right)
    {
        if (arr[i] < arr[j])
        {
            /* code */
            temp[index++] = arr[i++];
        }
        else
        {
            temp[index++] = arr[j++];
        }
        
    }
    while (i<=mid)
    {
        /* code */
        temp[index++] = arr[i++];
    }
    while (j<=right)
    {
        /* code */
        temp[index++] = arr[j++];
    }

    // 将合并后的数据拷贝到原始队列，偏移量= left
    for (int k = 0; k < index; k++)
    {
        /* code */
        arr[left + k] = temp[k];
    } 
}

// temp 用来合并归并排序后的结果
void merge_sort_hqq(vector<int>& arr, int left, int right, vector<int>& temp)
{
    // 设置递归退出的条件
    if (left >= right)
    {
        /* code */
        return;
    }

    // 对数组进行拆分, 防止 left+right 越界
    int mid = left + (right - left) / 2;
    
    // 对左侧和右侧，递归进行处理。
    merge_sort_hqq(arr, left, mid, temp);
    merge_sort_hqq(arr, mid+1, right, temp);

    // 合并两个有序数组(子序列)
    merge_sorted_array_hqq(arr,left,right, temp);   
}

int main() {
    std::vector<int> arr = {38, 27, 43,25, 47,23, 68};

    std::cout << "Original array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    // mergeSort(arr, 0, arr.size() - 1);
    vector<int> temp(arr.size());
    merge_sort_hqq(arr, 0, arr.size()-1, temp);

    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}