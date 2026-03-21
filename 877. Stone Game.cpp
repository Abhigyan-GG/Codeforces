"#Stone Game Problem 877 LeetCode"

"for optimal solution, O(1)"
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

"For Dp Solution, O(n^2)"
 class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: one pile
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }

        // Fill DP table
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;

                dp[i][j] = max(
                    piles[i] - dp[i + 1][j],
                    piles[j] - dp[i][j - 1]
                );
            }
        }

        return dp[0][n - 1] > 0;
    }
};