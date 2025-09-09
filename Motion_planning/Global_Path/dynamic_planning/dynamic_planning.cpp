#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// m行n列的网格，每个格子有代价cost[i][j]
int minPathSum(const vector<vector<int>>& cost) {
    int m = cost.size(), n = cost[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = cost[0][0];
    // 初始化第一行和第一列
    for (int i = 1; i < m; ++i) dp[i][0] = dp[i-1][0] + cost[i][0];
    for (int j = 1; j < n; ++j) dp[0][j] = dp[0][j-1] + cost[0][j];
    // 状态转移
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j];
    return dp[m-1][n-1];
}

int main() {
    vector<vector<int>> cost = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    cout << "最短路径和: " << minPathSum(cost) << endl;
    return 0;
}