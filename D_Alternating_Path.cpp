#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 1e9+7;

bool dfs(ll u, vector<vector<ll>>& adj, vector<ll>& vis, ll c, ll& ct0, ll& ct1) {
    vis[u] = c;
    if (c) ct1++;
    else ct0++;

    bool bip = true;
    for (ll v : adj[u]) {
        if (vis[v] == -1) {
            if (!dfs(v, adj, vis, !c, ct0, ct1)) bip = false;
        } else if (vis[v] == vis[u]) {
            bip = false;
        }
    }
    return bip;
}

void solve() {
    ll n, m; 
    cin >> n >> m;

    vector<vector<ll>> adj(n);
    for (ll i = 0; i < m; i++) {
        ll u, v; 
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> vis(n, -1);
    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        if (vis[i] != -1) continue;

        ll ct0 = 0, ct1 = 0;
        if (dfs(i, adj, vis, 0, ct0, ct1)) {
            ans += max(ct0, ct1);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; 
    cin >> t;
    while (t--) solve();
}