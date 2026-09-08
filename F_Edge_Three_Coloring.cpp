#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const int MAXM = 3015;

struct Edge {
    int u, v;
};

int n, m;
vector<Edge> edges;
vector<vector<pair<int,int>>> g;
vector<int> parent, parentEdge, depth;
vector<bool> used;
vector<bitset<MAXM>> basis;

void dfs(int u, int p) {
    for (auto [v, id] : g[u]) {
        if (v == p) continue;
        if (used[v]) continue;

        used[v] = true;
        parent[v] = u;
        parentEdge[v] = id;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

bitset<MAXM> getCycle(int id) {
    bitset<MAXM> res;
    int u = edges[id].u;
    int v = edges[id].v;

    res[id] = 1;

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

bool connectedWithout(const bitset<MAXM>& removed) {
    vector<int> vis(n, 0);
    queue<int> q;

    q.push(0);
    vis[0] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [v, id] : g[u]) {
            if (removed[id]) continue;
            if (vis[v]) continue;

            vis[v] = 1;
            q.push(v);
        }
    }

    for (int x : vis) {
        if (!x) return false;
    }

    return true;
}

bool isSimpleCycle(const bitset<MAXM>& s) {
    vector<int> deg(n, 0);
    int cnt = 0;

    for (int i = 0; i < m; ++i) {
        if (s[i]) {
            deg[edges[i].u]++;
            deg[edges[i].v]++;
            cnt++;
        }
    }

    if (cnt < 3) return false;

    for (int i = 0; i < n; ++i) {
        if (deg[i] != 0 && deg[i] != 2)
            return false;
    }

    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 2) {
            start = i;
            break;
        }
    }

    vector<int> vis(n, 0);
    queue<int> q;
    q.push(start);
    vis[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [v, id] : g[u]) {
            if (!s[id]) continue;
            if (vis[v]) continue;

            vis[v] = 1;
            q.push(v);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (deg[i] && !vis[i])
            return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    edges.resize(m);
    g.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        edges[i] = {u, v};
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    parent.assign(n, -1);
    parentEdge.assign(n, -1);
    depth.assign(n, 0);
    used.assign(n, false);

    used[0] = true;
    dfs(0, -1);

    vector<bool> inTree(m, false);

    for (int v = 1; v < n; ++v) {
        inTree[parentEdge[v]] = true;
    }

    for (int i = 0; i < m; ++i) {
        if (!inTree[i])
            basis.push_back(getCycle(i));
    }

    int r = basis.size();

    for (int mask = 1; mask < (1 << r); ++mask) {
        bitset<MAXM> cur;

        for (int j = 0; j < r; ++j) {
            if (mask & (1 << j))
                cur ^= basis[j];
        }

        if (!isSimpleCycle(cur))
            continue;

        if (connectedWithout(cur)) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}