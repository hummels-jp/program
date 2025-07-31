#include <vector>
#include <iostream>
using namespace std;

void shell_sort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // from 0 to gap-1 is the first element in each gap, and not need to move
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            // 插入排序，间隔为 gap
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    shell_sort(arr);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}