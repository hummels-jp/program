#include <vector>
#include <iostream>
using namespace std;

int left_partition(vector<int>& arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (true)
    {
        /* code */
        // left, find item bigger than pivot
        while (i <= j && arr[i]<pivot)
        {
            /* code */
            i++;
        }

        // right, find item smaller than pivot
        while (i <=j && arr[j] > pivot)
        {
            /* code */
            j--;
        }

        if(i > j)
        {
            break;
        }

        swap(arr[i], arr[j]);
        i++;
        j--;

    }

    // place the pivot, left is j
    swap(arr[left], arr[j]);
    return j;
}



void quick_sort(vector<int>& arr, int left, int right) {
    if(left < right)
    {
        int partition_index = left_partition(arr, left, right);

        quick_sort(arr, left, partition_index -1);
        quick_sort(arr, partition_index + 1, right);
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