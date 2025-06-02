
#include <cmath>
#include <iostream>
using namespace std;

int arr[] = {12,6,7,11,16,3,8};
const int len = sizeof(arr) / sizeof(arr[0]);
int x[len] = {0}; // 子集树辅助数组
int bestx[len] = {0}; // 记录最优解的辅助数组
int sum_value = 0;
int remainder_value = 0;
int min_value = __INT_MAX__;

void helper(int arr[], int i, int len)
{
    // 递归结束的条件
    if (i== len)
    {
        /* code */
        if (min_value > abs(sum_value-remainder_value))
        {
            /* code */
            min_value = abs(sum_value-remainder_value);

            for (int j = 0; j < len; j++)
            {
                /* code */
                bestx[j] = x[j];
            }
            
        }
        
    }
    else
    {
        // 选择节点i
        x[i] = 1;
        sum_value+=arr[i];
        remainder_value -= arr[i];
        helper(arr, i+1, len);

        // 递归回退，不选择节点i
        sum_value-=arr[i];
        remainder_value+=arr[i];

        // 不选择节点i
        x[i] = 0;
        helper(arr, i+1, len);
    }
    
}

int main()
{
    for (int i = 0; i < len; i++)
    {
        /* code */
        remainder_value += arr[i];
    }

    helper(arr, 0, len);

    sum_value = 0;
    remainder_value = 0;


    for (int i = 0; i < len; i++)
    {
        /* code */
        if (bestx[i] == 1)
        {
            /* code */
            cout << arr[i] << " ";
            sum_value += arr[i];
        }
        
    }
    cout << endl;

    cout << "sum_value " << sum_value << endl;

    for (int i = 0; i < len; i++)
    {
        /* code */
        if (bestx[i] == 0)
        {
            /* code */
            cout << arr[i] << " ";
            remainder_value += arr[i];
        }
        
    }
    cout << endl;
    cout << "remainder_value " << remainder_value << endl;
    

    cout << min_value << endl;
    
    return 0;
}
