#include <vector>
#include <iostream>
using namespace std;

// 调整堆，使以 root 为根的子树满足最大堆性质
void heapify(vector<int>& arr, int heap_size, int root_index) {
    int largest_index = root_index;
    int left_index = 2* root_index + 1;
    int right_index = 2* root_index + 2;

    if (left_index < heap_size && arr[left_index] > arr[largest_index])
    {
        /* code */
        largest_index = left_index;
    }

    if (right_index < heap_size && arr[right_index] > arr[largest_index])
    {
        /* code */
        largest_index = right_index;
    }

    if (largest_index != root_index)
    {
        /* code */
        swap(arr[root_index], arr[largest_index]);

        heapify(arr, heap_size, largest_index);
    }   
}

void heap_sort(vector<int>& arr) {
    int size = arr.size();

    // create heap, heapify the non leaf node
    for (int i = size/2 -1; i >= 0; i--)
    {
        /* code */
        heapify(arr, size, i);
    }

    for (int i = size - 1; i >=0 ; i--)
    {
        /* code */
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