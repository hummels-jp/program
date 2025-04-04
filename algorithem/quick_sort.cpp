#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[left];
    int i = left, j = right;

    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        if (i < j) arr[i++] = arr[j];

        while (i < j && arr[i] <= pivot) i++;
        if (i < j) arr[j--] = arr[i];
    }

    arr[i] = pivot;

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

void quick_sort_hqq(vector<int>& arr, int left, int right)
{
    // 递归结束的条件
    if(left >= right)
    {
        return;
    }

    // 获得基准值
    int mid = (left+right)/2;
    int pivot = arr[mid];

    // 从基准值左侧递增开始与基准值比较。
    // 从基准值右侧递减开始与基准值比较。
    int begin = left;
    int end = right;

    while (begin <=end)
    {
        /* code */
        // 头部元素与基准数进行比较
        // begin 指针不能越界
        while (arr[begin] <=pivot&&begin <=end)
        {
            /* code */
            begin++;
        }
        // 尾部元素与基准数进行比较，end指针不能越界
        while (arr[end]>=pivot && end >= begin)
        {
            /* code */
            end--;
        }

        // 找到了头部大于基准的元素，尾部小于基准的元素,进行交换
        if (begin <= end)
        {
            /* code */
            swap(arr[begin], arr[end]);
            begin++;
            end--;
        }
    }

    // 左侧子序列
    quick_sort_hqq(arr, left, end); 
    // 右侧子序列
    quick_sort_hqq(arr, begin, right);
    
}

int main() {
    std::vector<int> arr = {34, 7, 23, 32, 5, 62};
    std::cout << "Original array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    // quickSort(arr, 0, arr.size() - 1);
    quick_sort_hqq(arr,0, arr.size()-1);

    std::cout << "Sorted array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}