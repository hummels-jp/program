#include <vector>
#include <iostream>
using namespace std;

// 使用左端作为基准
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1, j = right;
    while (true) {
        while (i <= j && arr[i] <= pivot) ++i;
        while (i <= j && arr[j] >= pivot) --j;
        if (i > j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[left], arr[j]);
    return j;
}

void quick_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quick_sort(arr, left, pi - 1);
        quick_sort(arr, pi + 1, right);
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    quick_sort(arr, 0, arr.size() - 1);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}