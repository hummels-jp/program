#include <vector>
#include <iostream>
using namespace std;

void select_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    select_sort(arr);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
        return 0;
}