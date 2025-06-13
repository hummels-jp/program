#include <iostream>
#include <cmath>
using namespace std;


int cnt = 0;
int dp[12] = {0};

int recurise_coin(int n)
{

    if (dp[n] > 0)
    {
        /* code */
        return dp[n];
    }
    

    cnt++;
    if (n ==1 || n ==3 || n==5)
    {
        /* code */
        dp[n] = 1;
    }
    else if (n ==2 || n == 4)
    {
        /* code */
        dp[n] = 2;
    }
    else
    {
        int n1 = recurise_coin(n -1) + 1; //  问题分解，先使用一个1分硬币
        int n2 = recurise_coin(n-2) + 1;
        int n3 = recurise_coin(n-3) + 1;

        dp[n] = min(min(n1, n2), n3);
    }
    
    return dp[n];
    
}



int main()
{
    int count = recurise_coin(11);
    cout << count << endl;
    cout << "cnt " << cnt << endl;
    return 0;
}