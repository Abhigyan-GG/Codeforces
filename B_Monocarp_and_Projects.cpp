#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long x, y, k;
        cin >> x >> y >> k;

        long long d = y - x;
        if (d == 0) {
            cout << 0 << '\n';
            continue;
        }

        long long ans = 0;
        long long special = 0;

        if (x <= d) {
            special = min(k, d - x + 1);

            for (long long i = 0; i < special; i++) {
                ans += d % (x + i);
            }
        }
        ans += (k - special) * d;

        cout << ans << '\n';
    }

    return 0;
}