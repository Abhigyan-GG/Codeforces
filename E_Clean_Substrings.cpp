#include <bits/stdc++.h>
using namespace std;

static char buf[200005];

struct SegTree {
    int n;
    vector<int> sum, lazy;
    void init(int n_) {
        n = n_;
        sum.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
    }
    void build(int node, int l, int r, vector<int>& arr) {
        if (l == r) { sum[node] = arr[l]; return; }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, arr);
        build(node * 2 + 1, mid + 1, r, arr);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
    }
    void apply(int node, int l, int r) {
        sum[node] = (r - l + 1) - sum[node];
        lazy[node] ^= 1;
    }
    void push(int node, int l, int r) {
        if (lazy[node]) {
            int mid = (l + r) / 2;
            apply(node * 2, l, mid);
            apply(node * 2 + 1, mid + 1, r);
            lazy[node] = 0;
        }
    }
    void update(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(node, l, r); return; }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
    }
    void flip(int l, int r) {
        if (l > r) return;
        update(1, 1, n, l, r);
    }
    long long total() { return sum[1]; }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, q;
        scanf("%d %d", &n, &q);
        scanf("%s", buf);
        int m = n - 1;
        vector<int> D(m + 1, 0);
        for (int i = 1; i <= m; i++) D[i] = (buf[i - 1] != buf[i]) ? 1 : 0;

        long long SumB = 0, SumC = 0;
        for (int i = 1; i <= m; i++) {
            SumB += (long long)i * D[i];
            SumC += (long long)i * i * D[i];
        }

        vector<long long> results;

        if (m == 0) {
            for (int k = 0; k <= q; k++) results.push_back(0);
            for (int k = 0; k < q; k++) { int idx; scanf("%d", &idx); }
        } else {
            SegTree st;
            st.init(m);
            vector<int> parity(m + 1, 0);
            int cur = 0;
            for (int i = 1; i <= m; i++) { cur ^= D[i]; parity[i] = cur; }
            st.build(1, 1, m, parity);

            auto compute = [&]() -> long long {
                long long sumDiff = (long long)(m + 1) * SumB - SumC;
                long long cnt1 = st.total();
                long long part2 = cnt1 * ((long long)(m + 1) - cnt1);
                return (sumDiff + part2) / 2;
            };

            results.push_back(compute());

            for (int k = 0; k < q; k++) {
                int idx;
                scanf("%d", &idx);
                int cands[2] = { idx - 1, idx };
                for (int c = 0; c < 2; c++) {
                    int j = cands[c];
                    if (j >= 1 && j <= m) {
                        int oldv = D[j];
                        int newv = oldv ^ 1;
                        long long delta = newv - oldv;
                        SumB += delta * j;
                        SumC += delta * (long long)j * j;
                        D[j] = newv;
                        st.flip(j, m);
                    }
                }
                results.push_back(compute());
            }
        }

        for (size_t i = 0; i < results.size(); i++) {
            printf("%lld%c", results[i], i + 1 == results.size() ? '\n' : ' ');
        }
    }
    return 0;
}