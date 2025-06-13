
#include <iostream>
using namespace std;

int arr[] = {1,2,3};
const int len = sizeof(arr) / sizeof(arr[0]);
int x[len] = {0}; // 用来记录元素是否被选择

void helper(int arr[], int i, int len)
{
    // 递归结束的条件
    if (i == len)
    {
        /* code */
        for (int  j = 0; j < len; j++)
        {
            /* code */
            if (x[j] == 1)
            {
                /* code */
                cout << arr[j] << " ";
            }
            
        }
        cout <<endl;
        
    }
    else
    {
        // 选择i，遍历左子树
        x[i] = 1; 
        helper(arr, i+1, len);

        // 不选择i，遍历右子树
        x[i] = 0;
        helper(arr, i+1, len);
    } 
}




int main()
{
    helper(arr, 0, len);
}