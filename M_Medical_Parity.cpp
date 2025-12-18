#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    const int INF = 1e9;

    while (t--) {
        string x, y;
        cin >> x >> y;
        int n = x.size();

        int dp0 = 0, dp1 = INF; 

        for (int i = 0; i < n; i++) {
            int xi = x[i] - '0';
            int yi = y[i] - '0';

            int ndp0 = INF, ndp1 = INF;

            ndp0 = min(
                dp0 + (0 != yi) + ((0 ^ 0) != xi),
                dp1 + (0 != yi) + ((0 ^ 1) != xi)
            );

            ndp1 = min(
                dp0 + (1 != yi) + ((1 ^ 0) != xi),
                dp1 + (1 != yi) + ((1 ^ 1) != xi)
            );

            dp0 = ndp0;
            dp1 = ndp1;
        }

        cout << min(dp0, dp1) << "\n";
    }

    return 0;
}