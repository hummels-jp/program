#include <iostream>
#include <vector>
using namespace std;

/*
quickSort函数是快速排序的递归实现，功能如下：

1. 递归终止条件：如果 left >= right，说明区间内没有元素或只有一个元素，直接返回。
2. 选取基准值 pivot：取当前区间最左边的元素 arr[left] 作为基准。
3. 设置两个指针 i 和 j，分别指向区间的左右端点。
4. 循环分区：
   - 从右向左(j--)找到第一个小于 pivot 的元素，放到左边 i 位置。
   - 从左向右(i++)找到第一个大于 pivot 的元素，放到右边 j 位置。
   - 重复上述过程，直到 i 和 j 相遇。
5. 将基准值 pivot 放到最终的分界点 i 处。
6. 对基准值左侧和右侧的子区间递归调用 quickSort，实现分治排序。

该实现采用原地交换，空间复杂度低，平均时间复杂度为 O(nlogn)。
*/

// 快速排序实现
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) --j;
        arr[i] = arr[j];
        while (i < j && arr[i] <= pivot) ++i;
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    quickSort(arr, 0, arr.size() - 1);
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
