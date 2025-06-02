#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) return s;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int maxLen = 1, start = 0;

        // 单个字符是回文
        for (int i = 0; i < n; ++i) dp[i][i] = true;

        // 枚举子串长度
        for (int L = 2; L <= n; ++L) {
            for (int i = 0; i <= n - L; ++i) {
                int j = i + L - 1;
                if (s[i] == s[j]) {
                    if (L == 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i+1][j-1];
                    }
                } else {
                    dp[i][j] = false;
                }
                if (dp[i][j] && L > maxLen) {
                    maxLen = L;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

int main() {
    Solution sol;
    string s;
    cout << "请输入字符串: ";
    cin >> s;
    cout << "最长回文子串: " << sol.longestPalindrome(s) << endl;
    return 0;
}