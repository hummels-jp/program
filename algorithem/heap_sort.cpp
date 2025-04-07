#include <iostream>
#include <vector>
using namespace std;

// Function to heapify a subtree rooted at index i
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Utility function to print an array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// 调整堆，使其成为最大堆
// 调整堆时，已经排序的元素不参与，所以len 不等于 arr.size()
// parent 当前要调整堆的父节点位置，可能是整棵树，也有可能是该树的左，右子树
void heap_adjust(vector<int>& arr, int len, int parent)
{
    // 只调整堆
    int maxIndex = parent;
    int left = 2*parent + 1;
    int right = 2* parent + 2;
    // 左节点与父节点进行比较，左节点越界检查
    if (left < len && arr[left] > arr[maxIndex])
    {
        /* code */
        maxIndex = left;
    }
    // 右节点与最大值进行比较，右节点越界检查
    if (right < len && arr[right] > arr[maxIndex])
    {
        /* code */
        maxIndex = right;
    }

    // 若最大值不是父节点值，则需要调整。
    if(maxIndex != parent)
    {
        swap(arr[parent], arr[maxIndex]);
        // 如果发生交换，需要检查交换后的子树是否是最大堆
        heap_adjust(arr, len, maxIndex);
    }
}

// 按照最大堆，进行排序
void heap_sort(vector<int>& arr)
{
    if (arr.empty())
    {
        /* code */
        return;
    }
    
    // 从最后一个非叶子节点开始调整,一直调整到根节点
    // 交换之前，不改变树的长度
    for (int i = arr.size()/2-1; i >= 0 ; i--)
    {
        /* code */
        heap_adjust(arr, arr.size(), i);
    }

    // 最大堆调整完成后，交换根节点与最后一个叶子节点的位置
    // 递归操作，需要退出条件,最后一个叶子节点位置：arr.size() -1
    // 当堆只剩下1个元素时，退出循环
    for (int i = arr.size()-1; i > 0; i--)
    {
        /* code */
        swap(arr[i], arr[0]);
        // 交换完成后，继续进行调整，去掉当前i对应的节点(已是上一轮的最大值)
        // 去掉1个元素后， 数组的长度= arrsize()-1, 就是i的值。
        // 堆调整，从完全二叉树的根节点开始
        heap_adjust(arr, i, 0);
    }
}

// 堆调整
// 调整完一次后，去掉最后一个叶子节点，因此数组的长度不等于 arr.size()
// 调整的父节点位置，从0 开始
void heap_adjust_hqq(vector<int>& arr, int len, int parent)
{
    int left = 2*parent + 1;
    int right = 2* parent + 2;
    int min_index = parent;
    // 最小的元素被交换到完全二叉树的最后一个叶子节点，逆序排列
    if (left < len && arr[left] < arr[min_index])
    {
        /* code */
        min_index = left;
    }
    if (right < len && arr[right] < arr[min_index])
    {
        /* code */
        min_index = right;
    }

    // parent 不是最小值，需要进行交换
    if (min_index != parent)
    {
        /* code */
        swap(arr[parent], arr[min_index]);

        // 对交换后的子树进行最小堆检查
        heap_adjust_hqq(arr,len, min_index);
    }   
}

void heap_sort_hqq(vector<int>& arr)
{
    if (arr.empty())
    {
        return;
        /* code */
    }

    // 从第最后一个非叶子节点进行堆检查，直到根节点0
    for (int  i = arr.size()/2 -1 ; i >= 0; i--)
    {
        /* code */
        // 在交换之前，完全二叉树的长度不发生变化
        heap_adjust_hqq(arr, arr.size(), i);
    }

    // 第一次最小堆完成后，将根节点与最后一个叶子节点进行交换
    // 递归进行，交换一次，减少一个叶子节点，直到完全二叉树剩下最后1个节点
    for (int i = arr.size()-1; i > 0; i--)
    {
        /* code */
        swap(arr[i], arr[0]);
        // 去掉最后一个叶子节点后，完全二叉树的长度为 arr.size()-1, 等于i
        // 堆调整，从根节点0开始。
        heap_adjust_hqq(arr,i, 0);
    }
    
    
    
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    cout << "Original array: ";
    printArray(arr);

    // heapSort(arr);
    heap_sort(arr);
    heap_sort_hqq(arr);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}