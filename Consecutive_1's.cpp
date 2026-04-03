class Solution {
  public:
    int countStrings(int n) {
        if (n == 1) return 2;
        if (n == 2) return 3;
        
        long long prev2 = 2;
        long long prev1 = 3;
        
        for (int i = 3; i <=n; i++){
            long long curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};