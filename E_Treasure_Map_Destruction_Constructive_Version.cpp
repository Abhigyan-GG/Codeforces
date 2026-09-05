#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> b(n);
    for (int &x : b) cin >> x;

    vector<int> diff(n + 1, 0);

    // For b[i] = d > 0, there must be NO treasure
    // at distance < d from i.
    for (int i = 0; i < n; i++) {
        if (b[i] <= 0) continue;

        int d = b[i];

        int l = max(0, i - d + 1);
        int r = min(n - 1, i + d - 1);

        if (l <= r) {
            diff[l]++;
            diff[r + 1]--;
        }
    }

    vector<int> forbidden(n);
    int cur = 0;

    for (int i = 0; i < n; i++) {
        cur += diff[i];
        forbidden[i] = (cur > 0);
    }

    string ans(n, '0');

    // b[i] = 0 -> treasure MUST be here.
    for (int i = 0; i < n; i++) {
        if (b[i] == 0) {
            if (forbidden[i]) {
                cout << -1 << '\n';
                return;
            }

            ans[i] = '1';
        }
    }

    // b[i] > 0 -> need treasure exactly b[i] away.
    for (int i = 0; i < n; i++) {
        if (b[i] <= 0) continue;

        int d = b[i];

        int L = i - d;
        int R = i + d;

        bool leftOK =
            (L >= 0 && !forbidden[L]);

        bool rightOK =
            (R < n && !forbidden[R]);

        if (!leftOK && !rightOK) {
            cout << -1 << '\n';
            return;
        }

        // If there is already a suitable treasure, we're done.
        if ((leftOK && ans[L] == '1') ||
            (rightOK && ans[R] == '1')) {
            continue;
        }

        // Otherwise choose one endpoint.
        if (leftOK)
            ans[L] = '1';
        else
            ans[R] = '1';
    }

    // There must be at least one treasure.
    if (ans.find('1') == string::npos) {
        for (int i = 0; i < n; i++) {
            if (!forbidden[i]) {
                ans[i] = '1';
                break;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}