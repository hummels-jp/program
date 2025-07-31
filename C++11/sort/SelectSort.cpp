#include <vector>
#include <iostream>
using namespace std;

void select_sort(vector<int>& arr) {
    int size = arr.size();

    for (int i = 0; i < size - 1; i++)
    {
        /* code */
        int min_idx = i;
        for (int  j = i+1; j < size; j++)
        {
            /* code */
            if (arr[min_idx] > arr[j])
            {
                /* code */
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            /* code */
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