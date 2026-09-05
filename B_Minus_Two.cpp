#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        unordered_map<int, int> freq;

        int odd = 0;
        int even0 = 0; // x % 4 == 0
        int even2 = 0; // x % 4 == 2

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;

            freq[x]++;

            if (x % 2 == 1) {
                odd++;
            } else if (x % 4 == 0) {
                even0++;
            } else {
                even2++;
            }
        }

        int ans = 0;

        // We can perform 0 operations.
        for (auto &[x, cnt] : freq) {
            ans = max(ans, cnt);
        }

        // After enough operations.
        ans = max(ans, odd);
        ans = max(ans, even0);
        ans = max(ans, even2);

        cout << ans << '\n';
    }

    return 0;
}