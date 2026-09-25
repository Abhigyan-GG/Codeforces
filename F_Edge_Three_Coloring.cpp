#include <bits/stdc++.h>
using namespace std;

const int MAXM = 3015;

struct Edge {
    int u, v;
};

int n, m;
vector<Edge> edges;
vector<vector<pair<int, int>>> g;
vector<int> parent, parentEdge, depth;
vector<char> vis;

void dfs(int u) {
    vis[u] = 1;

    for (auto [v, id] : g[u]) {
        if (vis[v]) continue;

        parent[v] = u;
        parentEdge[v] = id;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

bitset<MAXM> getCycle(int id) {
    bitset<MAXM> res;
    res[id] = 1;

    int u = edges[id].u;
    int v = edges[id].v;

    while (u != v) {
        if (depth[u] >= depth[v]) {
            res[parentEdge[u]] = 1;
            u = parent[u];
        } else {
            res[parentEdge[v]] = 1;
            v = parent[v];
        }
    }

    return res;
}

bool isCycle(const bitset<MAXM>& s) {
    vector<int> deg(n, 0);
    int cnt = 0;

    for (int i = 0; i < m; ++i) {
        if (s[i]) {
            ++deg[edges[i].u];
            ++deg[edges[i].v];
            ++cnt;
        }
    }

    if (cnt < 3) return false;

    int start = -1;

    for (int i = 0; i < n; ++i) {
        if (deg[i] != 0 && deg[i] != 2)
            return false;

        if (deg[i] == 2)
            start = i;
    }

    vector<char> seen(n, 0);
    queue<int> q;

    q.push(start);
    seen[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [v, id] : g[u]) {
            if (!s[id] || seen[v]) continue;

            seen[v] = 1;
            q.push(v);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (deg[i] && !seen[i])
            return false;
    }

    return true;
}

bool connectedAfterRemoving(const bitset<MAXM>& removed) {
    vector<char> seen(n, 0);
    queue<int> q;

    q.push(0);
    seen[0] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [v, id] : g[u]) {
            if (removed[id] || seen[v]) continue;

            seen[v] = 1;
            q.push(v);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!seen[i])
            return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m;

        edges.resize(m);
        g.assign(n, {});
        parent.assign(n, -1);
        parentEdge.assign(n, -1);
        depth.assign(n, 0);
        vis.assign(n, 0);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            edges[i] = {u, v};
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }

        dfs(0);

        vector<char> inTree(m, 0);

        for (int v = 1; v < n; ++v)
            inTree[parentEdge[v]] = 1;

        vector<bitset<MAXM>> basis;

        for (int i = 0; i < m; ++i) {
            if (!inTree[i])
                basis.push_back(getCycle(i));
        }

        int r = basis.size();
        bool ok = false;

        for (int mask = 1; mask < (1 << r); ++mask) {
            bitset<MAXM> cur;

            for (int j = 0; j < r; ++j) {
                if (mask & (1 << j))
                    cur ^= basis[j];
            }

            if (!isCycle(cur))
                continue;

            if (connectedAfterRemoving(cur)) {
                ok = true;
                break;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}