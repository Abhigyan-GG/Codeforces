#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int T = 10000;
constexpr int N = 5000;
constexpr ll mod = 1000000007;
constexpr ll inv2 = (mod + 1) >> 1;
constexpr ll inv4 = inv2 >> 1;
constexpr ll inv8 = inv4 >> 1;
constexpr ll inv16 = (inv8 + mod) >> 1;

ll dp[2][N + 1][2][2];
vector<pair<int, int>> query[N + 1];
ll ans[T];
int maxN[N + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        query[m].push_back({n, i});
        maxN[m] = max(maxN[m], n);
    }

    ll curr = 0;

    for (int m = 1; m <= N; m++) {
        if (query[m].empty()) continue;   // 🔥 skip unused m

        // clear dp
        for (int i = 0; i < 2; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k < 2; k++)
                    for (int l = 0; l < 2; l++)
                        dp[i][j][k][l] = 0;

        // initial state
        dp[0][0][0][0] = inv4 * inv4 % mod;
        dp[0][0][0][1] = inv4 * 3 % mod * inv4 % mod;
        dp[0][0][1][0] = 3 * inv4 % mod * inv4 % mod;
        dp[0][0][1][1] = 9 * inv16 % mod;

        curr = 0;

        for (int n = 1; n <= maxN[m]; n++) {
            int cur = n & 1;
            int pre = 1 - cur;

            for (int j = 0; j <= m; j++)
                for (int k = 0; k < 2; k++)
                    for (int l = 0; l < 2; l++)
                        dp[cur][j][k][l] = 0;

            for (int j = 0; j < m; j++) {

                for (int br = 0; br < 2; br++) {
                    ll p = dp[pre][j][0][br];
                    if (!p) continue;

                    dp[cur][j][0][0] = (dp[cur][j][0][0] + p * 3 % mod * inv16) % mod;
                    dp[cur][j][0][1] = (dp[cur][j][0][1] + p * 3 % mod * inv8) % mod;
                    dp[cur][j][1][0] = (dp[cur][j][1][0] + p * inv4) % mod;
                    dp[cur][j][1][1] = (dp[cur][j][1][1] + p * 5 % mod * inv16) % mod;
                }

                for (int br = 0; br < 2; br++) {
                    ll p = dp[pre][j][1][0];
                    if (!p) continue;

                    dp[pre][j + 1][0][0] = (dp[pre][j + 1][0][0] + p * 3 % mod * inv16) % mod;
                    dp[pre][j + 1][0][1] = (dp[pre][j + 1][0][1] + p * inv4) % mod;
                    dp[pre][j + 1][1][0] = (dp[pre][j + 1][1][0] + p * 3 % mod * inv8) % mod;
                    dp[pre][j + 1][1][1] = (dp[pre][j + 1][1][1] + p * 5 % mod * inv16) % mod;
                }

                curr = (curr + dp[pre][j][1][1]) % mod;
            }

            for (int bd = 0; bd < 2; bd++) {
                ll p = dp[pre][m - 1][bd][0];
                if (!p) continue;

                if (bd == 0) {
                    dp[cur][m - 1][0][0] = (dp[cur][m - 1][0][0] + p * inv4) % mod;
                    dp[cur][m - 1][1][0] = (dp[cur][m - 1][1][0] + p * 3 % mod * inv4) % mod;
                } else {
                    curr = (curr + p) % mod;
                }
            }

            for (auto &p : query[m]) {
                if (p.first == n) {
                    ll success = (1 - curr + mod) % mod;
                    ll power = 1, base = 4;
                    ll exp = (ll)(n + 1) * (m + 1);
                    while (exp) {
                        if (exp & 1) power = power * base % mod;
                        base = base * base % mod;
                        exp >>= 1;
                    }
                    ans[p.second] = success * power % mod;
                }
            }
        }
    }

    for (int i = 0; i < t; i++)
        cout << ans[i] << ' ';
}
