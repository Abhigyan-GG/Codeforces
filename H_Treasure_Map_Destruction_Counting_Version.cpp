#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const ll MOD = 1000000007LL;

void solve() {
    int n;
    cin >> n;

    vector<int> b(n);
    for (int &x : b) cin >> x;
    vector<char> forcedZero(n, false);
    vector<char> forcedOne(n, false);

    vector<int> diff(n + 1, 0);

    bool anyKnown = false;

    for (int i = 0; i < n; ++i) {
        if (b[i] == -1)
            continue;

        anyKnown = true;

        if (b[i] == 0) {
            forcedOne[i] = true;
        } else {
            int d = b[i];

            int l = max(0, i - d + 1);
            int r = min(n - 1, i + d - 1);

            diff[l]++;
            diff[r + 1]--;
        }
    }

    int cur = 0;

    for (int i = 0; i < n; ++i) {
        cur += diff[i];
        forcedZero[i] = (cur > 0);
    }

    for (int i = 0; i < n; ++i) {
        if (forcedZero[i] && forcedOne[i]) {
            cout << 0 << '\n';
            return;
        }
    }

    if (!anyKnown) {
        ll ans = 1;

        for (int i = 0; i < n; ++i)
            ans = ans * 2 % MOD;

        ans = (ans - 1 + MOD) % MOD;

        cout << ans << '\n';
        return;
    }

    vector<vector<int>> graph(n);

    for (int i = 0; i < n; ++i) {
        if (b[i] <= 0)
            continue;

        int d = b[i];

        int L = i - d;
        int R = i + d;

        bool leftOK =
            (L >= 0 && L < n && !forcedZero[L]);

        bool rightOK =
            (R >= 0 && R < n && !forcedZero[R]);

        if (!leftOK && !rightOK) {
            cout << 0 << '\n';
            return;
        }

        if (leftOK && !rightOK) {
            forcedOne[L] = true;
        }
        else if (!leftOK && rightOK) {
            forcedOne[R] = true;
        }
        else {
            if (!forcedOne[L] && !forcedOne[R]) {
                graph[L].push_back(R);
                graph[R].push_back(L);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (forcedZero[i] && forcedOne[i]) {
            cout << 0 << '\n';
            return;
        }
    }

    vector<char> visited(n, false);

    vector<int> parent(n, -1);
    vector<ll> dp0(n, 0), dp1(n, 0);
    vector<int> order;
    order.reserve(n);
    vector<int> st;  
    st.reserve(n);

    ll answer = 1;

    for (int root = 0; root < n; ++root) {

        if (forcedZero[root] || visited[root])
            continue;

        order.clear();
        st.clear();
        st.push_back(root);
        visited[root] = true;

        while (!st.empty()) {
            int v = st.back();
            st.pop_back();

            order.push_back(v);

            for (int u : graph[v]) {
                if (visited[u])
                    continue;

                visited[u] = true;
                parent[u] = v;
                st.push_back(u);
            }
        }

        for (int idx = (int)order.size() - 1;
             idx >= 0;
             --idx) {

            int v = order[idx];

            if (forcedOne[v]) {
                dp0[v] = 0;
                dp1[v] = 1;
                continue;
            }

            dp0[v] = 1;
            dp1[v] = 1;

            for (int u : graph[v]) {

                if (parent[u] != v)
                    continue;

                dp0[v] =
                    dp0[v] * dp1[u] % MOD;

                dp1[v] =
                    dp1[v] *
                    ((dp0[u] + dp1[u]) % MOD)
                    % MOD;
            }
        }

        answer =
            answer *
            ((dp0[root] + dp1[root]) % MOD)
            % MOD;
    }

    cout << answer << '\n';
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