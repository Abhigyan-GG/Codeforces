#include <bits/stdc++.h>
using namespace std;

int n, k;
int cnt[101];
long double q[31][31];
long double dp[31][31][31];
bool vis[31][31][31];

long double solve(int w, int l, int t) {
    if (t == 0) return 1.0L;
    if (vis[w][l][t]) return dp[w][l][t];
    vis[w][l][t] = true;

    long double p = q[w][l];
    long double bet = p * 2.0L * solve(w + 1, l, t - 1);
    long double obs = p * solve(w + 1, l, t - 1)
                    + (1.0L - p) * solve(w, l + 1, t - 1);

    return dp[w][l][t] = max(bet, obs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    static long double pw1[101][31], pw0[101][31];

    for (int i = 0; i <= 100; i++) {
        long double pi = i / 100.0L;
        pw1[i][0] = pw0[i][0] = 1.0L;
        for (int j = 1; j <= k; j++) {
            pw1[i][j] = pw1[i][j - 1] * pi;
            pw0[i][j] = pw0[i][j - 1] * (1.0L - pi);
        }
    }

    for (int w = 0; w <= k; w++) {
        for (int l = 0; w + l <= k; l++) {
            long double num = 0.0L, den = 0.0L;
            for (int i = 0; i <= 100; i++) {
                if (!cnt[i]) continue;
                long double v = pw1[i][w] * pw0[i][l] * cnt[i];
                den += v;
                num += (i / 100.0L) * v;
            }
            q[w][l] = (den == 0.0L ? 0.0L : num / den);
        }
    }

    long double ans = 1000.0L * (solve(0, 0, k) - 1.0L);
    cout << fixed << setprecision(15) << ans << "\n";
}