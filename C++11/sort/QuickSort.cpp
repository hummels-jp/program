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
        // left
        while (i<=j && arr[i] <= pivot)
        {
            /* code */
            i++;
        }

        // right
        while (i<=j && arr[j] >= pivot)
        {
            /* code */
            j--;
        }

        if (i > j)
        {
            /* code */
            break;
        }

        swap(arr[i], arr[j]);    
    }
    swap(arr[left], arr[j]);

    return j;
}

int right_partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quick_sort(vector<int>& arr, int left, int right) {
    if(left < right)
    {
        // int partition_index = left_partition(arr, left, right);
        int partition_index = right_partition(arr, left, right);

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