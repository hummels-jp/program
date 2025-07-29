#include <vector>
#include <iostream>
using namespace std;

void insert_sort(vector<int>& arr) {
    int size = arr.size();
    for (int  i = 1; i < size; i++)
    {
        /* code */
        int key = arr[i];
        int j = i-1;
        
        while (j>=0 && arr[j]> key)
        {
            /* code */
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    insert_sort(arr);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}