#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minPathSum(const vector<vector<int>>& cost, int target_row, int target_column)
{
    int m = cost.size();
    int n = cost[0].size();
    vector<vector<int>> dp = vector(m, vector(n, 0));

    dp[0][0] = cost[0][0];

    // 1 initial the first row 
    for(int i =1; i< n; i++)
    {
        dp[0][i] = dp[0][i-1] + cost[0][i-1];
    }

    // 2 intial the first column
    for(int j = 1; j< m; j++)
    {
        dp[j][0] = dp[j-1][0] + cost[j-1][0]; 
    }

    // 3 state transition equation
    for(int i =1; i < m; i++)
    {
        for(int j=1; j<n; j++)
        {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j];
        }
    }

    // 4 return the target value
    return dp[target_row-1][target_column-1];
}

int main() {
    vector<vector<int>> cost = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    cout << "最短路径和: " << minPathSum(cost, 2, 2) << endl;
    return 0;
}