#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        long long ans = (1LL << (n - k + 1)) + 2LL * (k - 1);

        cout << ans << '\n';
    }

    return 0;
}