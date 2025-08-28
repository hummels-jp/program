#include <vector>
#include <iostream>
using namespace std;

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    // loop index, find the max of the array in each loop
    for (int i = 0; i < n - 1; ++i) {
        // indicate weather the array is alread sorted
        bool swapped = false;
        // compare with arr[j] and arr[j+1], get the max into the bottom
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // 如果本轮没有交换，说明已排序
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    bubble_sort(arr);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}