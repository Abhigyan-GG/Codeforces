#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2];
    int cnt;

    Node() : ch{-1, -1}, cnt(0) {}
};

struct PairState {
    int u, v;
};

struct Solver {
    vector<Node> trie;
    vector<unsigned> result;

    long long ways(int u, int v) {
        if (u == v)
            return 1LL * trie[u].cnt * (trie[u].cnt - 1) / 2;
        return 1LL * trie[u].cnt * trie[v].cnt;
    }

    void split(
        const vector<PairState>& cur,
        vector<PairState>& zero,
        vector<PairState>& one,
        long long& zeroCount
    ) {
        zero.clear();
        one.clear();
        zeroCount = 0;

        if (zero.capacity() < cur.size() * 2)
            zero.reserve(cur.size() * 2);

        if (one.capacity() < cur.size() * 2)
            one.reserve(cur.size() * 2);

        for (auto [u, v] : cur) {
            if (u == v) {
                int a = trie[u].ch[0];
                int b = trie[u].ch[1];

                if (a != -1) {
                    long long w = ways(a, a);
                    if (w) {
                        zero.push_back({a, a});
                        zeroCount += w;
                    }
                }

                if (b != -1) {
                    long long w = ways(b, b);
                    if (w) {
                        zero.push_back({b, b});
                        zeroCount += w;
                    }
                }

                if (a != -1 && b != -1) {
                    long long w = ways(a, b);
                    if (w)
                        one.push_back({a, b});
                }
            } else {
                int a0 = trie[u].ch[0];
                int a1 = trie[u].ch[1];
                int b0 = trie[v].ch[0];
                int b1 = trie[v].ch[1];

                if (a0 != -1 && b0 != -1) {
                    long long w = ways(a0, b0);
                    if (w) {
                        zero.push_back({a0, b0});
                        zeroCount += w;
                    }
                }

                if (a1 != -1 && b1 != -1) {
                    long long w = ways(a1, b1);
                    if (w) {
                        zero.push_back({a1, b1});
                        zeroCount += w;
                    }
                }

                if (a0 != -1 && b1 != -1) {
                    long long w = ways(a0, b1);
                    if (w)
                        one.push_back({a0, b1});
                }

                if (a1 != -1 && b0 != -1) {
                    long long w = ways(a1, b0);
                    if (w)
                        one.push_back({a1, b0});
                }
            }
        }
    }

    void emitAll(
        const vector<PairState>& cur,
        int bit,
        unsigned pref
    ) {
        if (cur.empty())
            return;

        if (bit < 0) {
            for (auto [u, v] : cur) {
                long long w = ways(u, v);
                result.insert(result.end(), (size_t)w, pref);
            }
            return;
        }

        vector<PairState> zero, one;
        long long zeroCount;

        split(cur, zero, one, zeroCount);

        emitAll(zero, bit - 1, pref);
        emitAll(one, bit - 1, pref | (1u << bit));
    }

    vector<unsigned> transform(const vector<unsigned>& a) {
        int n = a.size();

        trie.clear();
        trie.reserve((size_t)n * 31 + 1);
        trie.emplace_back();

        for (unsigned x : a) {
            int u = 0;
            ++trie[u].cnt;

            for (int bit = 29; bit >= 0; --bit) {
                int b = (x >> bit) & 1u;

                if (trie[u].ch[b] == -1) {
                    trie[u].ch[b] = trie.size();
                    trie.emplace_back();
                }

                u = trie[u].ch[b];
                ++trie[u].cnt;
            }
        }

        result.clear();
        result.reserve(n);

        vector<PairState> cur{{0, 0}};
        vector<PairState> zero, one;

        long long remaining = n;
        unsigned pref = 0;

        for (int bit = 29; bit >= 0; --bit) {
            long long zeroCount;
            split(cur, zero, one, zeroCount);

            if (zeroCount >= remaining) {
                cur.swap(zero);
            } else {
                emitAll(zero, bit - 1, pref);

                remaining -= zeroCount;
                pref |= (1u << bit);

                cur.swap(one);
            }
        }

        for (auto [u, v] : cur) {
            if (remaining == 0)
                break;

            long long w = ways(u, v);
            long long take = min(remaining, w);

            result.insert(result.end(), (size_t)take, pref);
            remaining -= take;
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<unsigned> a(n);
        for (auto& x : a)
            cin >> x;

        vector<unsigned long long> queries(q);
        for (auto& x : queries)
            cin >> x;

        sort(a.begin(), a.end());

        vector<unsigned long long> ans;

        for (int step = 0; step <= 64; ++step) {
            ans.push_back((unsigned long long)a.back() - a.front());

            if (ans.back() == 0)
                break;

            Solver solver;
            a = solver.transform(a);
        }

        for (auto x : queries) {
            if (x < ans.size())
                cout << ans[x] << '\n';
            else
                cout << 0 << '\n';
        }
    }

    return 0;
}