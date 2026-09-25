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

        vector<int> pos(n + 1);

        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            pos[x] = i;
        }

        vector<int> p(n + 1);

        for (int x = 1; x <= n; x++)
            p[x] = pos[x] & 1;

        const int INF = 1e9;

        int lo[2] = {0, INF};
        int hi[2] = {0, -INF};

        for (int i = 1; i < n; i++) {
            int nlo[2] = {INF, INF};
            int nhi[2] = {-INF, -INF};

            for (int parity = 0; parity < 2; parity++) {
                if (lo[parity] > hi[parity])
                    continue;

                int needLeft = (parity + 1) & 1;
                int needRight = (n - i + 1 + parity) & 1;

                if (p[i] == needLeft) {
                    int np = parity ^ 1;
                    nlo[np] = min(nlo[np], lo[parity] + 1);
                    nhi[np] = max(nhi[np], hi[parity] + 1);
                }

                if (p[i] == needRight) {
                    int np = parity;
                    nlo[np] = min(nlo[np], lo[parity]);
                    nhi[np] = max(nhi[np], hi[parity]);
                }
            }

            lo[0] = nlo[0];
            lo[1] = nlo[1];
            hi[0] = nhi[0];
            hi[1] = nhi[1];
        }

        int required = p[n] ^ 1;

        cout << (lo[required] <= hi[required] ? "YES\n" : "NO\n");
    }

    return 0;
}