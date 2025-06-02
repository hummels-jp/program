
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int arr[] = {12,6,7,11,16,3,8,9};
const int len = sizeof(arr) / sizeof(arr[0]);
// int x[len] = {0}; // 子集树辅助数组
// int bestx[len] = {0}; // 记录最优解的辅助数组
vector<int> x; // 子集树辅助数组
vector<int> bestx; // 记录最优解的辅助数组
int sum_value = 0;
int remainder_value = 0;
int min_value = __INT_MAX__;
int cnt = 0; // 记录遍历子节点的次数
int unprocessed_cnt = len;

void helper(int i)
{
    // 递归结束的条件
    if (i== len)
    {
        cnt ++;
        /* code */
        if (min_value > abs(sum_value-remainder_value))
        {
            /* code */
            min_value = abs(sum_value-remainder_value);
            bestx = x;
            
        }
        
    }
    else
    {
        // 处理当前节点 i
        unprocessed_cnt --; 
        // 选择节点i
        // x[i] = 1;
        // 对左子树进行剪枝操作，只有到选择的元素数目小于N时，才可以加入新的元素。
        /* code */
        if (x.size() < len/2)
        {
            /* code */
            x.push_back(arr[i]);
            sum_value+=arr[i];
            remainder_value -= arr[i];
            helper(i+1);

            // 递归回退，不选择节点i
            sum_value-=arr[i];
            remainder_value+=arr[i];
            x.pop_back();
        }
        
        // 不选择节点i
        // 右子树剪枝， 已选数字个数 + 未选择数字个数 >= len/2
        if (x.size() + unprocessed_cnt >= len/2)
        {
            /* code */
            helper(i+1);
        }
        
        // 当前节点i已经处理完成，回溯到其父节点， 节点i处于未处理状态。
        unprocessed_cnt ++;
    }
    
}

int main()
{
    for (int i = 0; i < len; i++)
    {
        /* code */
        remainder_value += arr[i];
    }

    helper(0);

    // sum_value = 0;
    // for (auto it : bestx)
    // {
    //     cout << it << " ";
    //     sum_value += it;
    // }
    // cout << endl;

    // remainder_value = 0;
    // for (int i = 0; i < len; i++)
    // {
    //     /* code */
    //     remainder_value += arr[i];
    // }
    // remainder_value -= sum_value;


    // cout << "sum_value " << sum_value << endl;
    // cout << "remainder_value " << remainder_value << endl;

    // cout << endl;
    // cout << "remainder_value " << remainder_value << endl;
    
    cout << "min_value " <<min_value << endl;
    cout << "cnt " << cnt << endl;
    
    return 0;
}
