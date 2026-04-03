class Solution {
  public:
    vector<int> diagView(vector<vector<int>> mat) {
        int n = mat.size();
        vector<int> result;
            for (int s = 0; s <= 2 * n - 2; s++) {
                int start = max(0, s - (n - 1));
                int end = min(n - 1, s);
                                                    
            for (int i = start; i <= end; i++) {
                int j = s - i;
                result.push_back(mat[i][j]);
            }
        }
        return result;

    }    
};