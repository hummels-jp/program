#include <vector>
#include <iostream>
using namespace std;

// 调整堆，使以 root 为根的子树满足最大堆性质
void heapify(vector<int>& arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();
    // 建堆, 调整非叶子节点， 得到最大堆
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    
    // 取出最大元素，放到末尾
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    heap_sort(arr);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}