#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, x;
        cin >> n >> x;

        vector<int> primes;

        for (int p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                primes.push_back(p);
                while (x % p == 0)
                    x /= p;
            }
        }

        if (x > 1)
            primes.push_back(x);

        vector<long long> sum(primes.size(), 0);

        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;

            for (int j = 0; j < (int)primes.size(); j++) {
                if (a % primes[j] == 0)
                    sum[j] += a;
            }
        }

        long long ans = 0;

        for (long long s : sum)
            ans = max(ans, s);

        cout << ans << '\n';
    }

    return 0;
}