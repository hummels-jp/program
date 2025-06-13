#include <vector>
#include <iostream>
using namespace std;

int arr[] = {1, 2, 3};
const int len = 3;
bool state[len] = {false}; // 记录每个元素被选择的状态
vector<int> nums; // 记录被选择的元素

void helper(int arr[], int i, int len)
{
    if (i==len)
    {
        /* code */
        for (int val : nums)
        {
            /* code */
            cout << val << " ";
        }
        cout << endl;
        
    }
    else
    {
        for (int k = 0; k < len; k++)
        {
            /* code */
            // 节点i 被选择
            if (state[k] == false)
            {
                /* code */
                state[k] = true;
                nums.push_back(arr[k]);
                // 递归处理节点i的子节点
                helper(arr, i+1, len);
                nums.pop_back();
                state[k] = false;
            }
        }
        
    }
    
}

int main()
{
    helper(arr, 0, len);
    return 0;
}