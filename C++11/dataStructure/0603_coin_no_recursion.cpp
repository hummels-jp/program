#include <iostream>
using namespace std;



int main()
{
    int coin_values[] = {1, 3, 5};
    int coin_count = 3;
    int wanted_value = 11;
    int* dp = new int[wanted_value + 1]();

    for (int i = 0; i <=wanted_value; i++)
    {
        /* code */
        dp[i] = i; // 默认全部由1分硬币组成。
        for (int j = 0; j < coin_count; j++)
        {
            /* code */
            // 当前要的值，大于单个硬币的值
            // 存在有其他组合，优于1分硬币组合
            if (i>=coin_values[j] && dp[i] > (1 + dp[i-coin_values[j]]))
            {
                /* code */
                dp[i] = 1 + dp[i-coin_values[j]];
            }
        }
    }
    
    cout << dp[wanted_value] << endl;
    delete[] dp;
    return 0;
}