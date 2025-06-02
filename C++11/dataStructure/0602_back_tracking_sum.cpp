#include <vector>
#include <iostream>
using namespace std;

int arr[] ={2,4,9,11,12,13};
const int len = sizeof(arr)/sizeof(arr[0]);
int target = 18;
vector<int> x; // 辅助数组，用来记录被选择的数

void helper(int i, int target)
{
    // 找到符合条件的子数组
    if (target == 0)
    {
        /* code */
        for (int value : x)
        {
            /* code */
            cout << value << " ";
        }
        cout << endl;
        
    }  

    // 递归，查找
    else
    {   
        // 递归调用剩下的元素，构建子树
        for (int j =i; j < len; j++)
        {
            // 如果剩下的元素小于需要构建的数字，向下递归
            if (target > arr[j])
            {
                /* code */
                x.push_back(arr[j]);
                helper(j+1, target - arr[j]); // 不允许重复选择元素
                x.pop_back();
            }
        }  
    }
    
}

int main()
{
    helper(0, target);

    return 0;
}