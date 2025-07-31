#include <vector>
#include <iostream>
using namespace std;

void shell_sort(vector<int>& arr) {
    int size = arr.size();
    for (int gap = size/2; gap >0;  gap/=2)
    {
        for (int i = gap; i < size; i++)
        {
            /* code */
            int key = arr[i];
            int j = i-gap;

            while (j>=0 && arr[j]> key)
            {
                /* code */
                arr[j+gap] = arr[j];
                j-=gap;
            }

            arr[j+gap] = key;
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