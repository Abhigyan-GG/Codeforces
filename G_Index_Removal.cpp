#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // x[i] = a[i] - i*k
    vector<ll> x(n + 1);

    // __int128 because prefix sums of x can exceed long long
    vector<i128> pref(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        x[i] = a[i] - 1LL * i * k;
        pref[i] = pref[i - 1] + (i128)x[i];
    }

    vector<ll> ans(n + 1, 0);

    // Removing first or last element keeps array good.
    ans[1] = 0;
    ans[n] = 0;

    for (int i = 2; i < n; i++) {

        // We need x[j] > threshold
        // threshold = a[i-1] - i*k
        ll threshold = a[i - 1] - 1LL * i * k;

        int L = i + 1;
        int R = n;
        int last = i;

        // x[] is non-increasing.
        // Find last j with x[j] > threshold.
        while (L <= R) {
            int mid = L + (R - L) / 2;

            if (x[mid] > threshold) {
                last = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }

        if (last >= i + 1) {
            int cnt = last - i;

            i128 sumX = pref[last] - pref[i];

            i128 res = sumX - (i128)cnt * threshold;

            ans[i] = (ll)res;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }
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