#include <vector>
#include <iostream>
using namespace std;

void quick_sort(vector<int>& arr, int left, int right)
{
    if (left>=right)
    {
        /* code */
        return;
    }

    int pivot = arr[left];
    int i = left;
    int j = right;
    while (i < j)
    {
        // compare the right 
        while (i < j && arr[j] >= pivot) // 应为 >=，否则重复元素会出错
        {
            j--;
        }
        arr[i] = arr[j];

        while (i < j && arr[i] <= pivot) // 应为 <=，否则重复元素会出错
        {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = pivot;

    quick_sort(arr, left, i-1);
    quick_sort(arr, i+1, right);
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    quick_sort(arr, 0, arr.size() - 1);
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}