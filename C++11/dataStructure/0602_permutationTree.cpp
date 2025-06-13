#include <vector>
#include <iostream>
using namespace std;

int arr[] = {1, 2, 3, 4};
const int len = 4;


void swap_data(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void helper(int arr[], int i, int len)
{
    //  到达子树
    if (i==len)
    {
        /* code */
        for (int j = 0; j < len; j++)
        {
            /* code */
            cout << arr[j] << " ";
        }
        cout << endl;
        
    }
    else
    {
        // 从当前节点进入子孩子节点
        for (int  k = i; k < len; k++)
        {
            /* code */
            swap_data(arr, i, k);
            helper(arr, i+1, len);
            swap_data(arr, i, k);
        }
        
    }
    
}

int main()
{
    helper(arr, 0, len);
    return 0;
}