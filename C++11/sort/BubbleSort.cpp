#include <vector>
#include <iostream>
using namespace std;

void bubble_sort(vector<int>& arr) {
    int size = arr.size();
    for (int i = 0; i < size-1; i++)
    {
        bool swapped = false;
        /* code */
        for (int j = 0; j < size - i - 1; j++)
        {
            /* code */
            if (arr[j] > arr[j+1])
            {
                /* code */
                swap(arr[j], arr[j+1]);
                swapped = true;
            }  
        }

        if (swapped == false)
        {
            /* code */
            break;
        }
        
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