
#include <bits/stdc++.h>
using namespace std;

struct Solver {
    int j, k;
    vector<int> values, lg;
    vector<vector<int>> st;
    map<int, vector<int>> positions;
    unordered_map<unsigned long long, unsigned char> memo;

    unsigned long long key(int l, int r) const {
        return (static_cast<unsigned long long>(
                    static_cast<unsigned int>(l)) << 32)
             | static_cast<unsigned int>(r);
    }

    int rangeMax(int l, int r) const {
        if (l > r) return 0;

        int level = lg[r - l + 1];
        return max(st[level][l],
                   st[level][r - (1 << level) + 1]);
    }

    pair<int, int> firstLast(int value, int l, int r) const {
        const auto &v = positions.at(value);

        auto first = lower_bound(v.begin(), v.end(), l);
        auto after = upper_bound(v.begin(), v.end(), r);

        return {*first, *(after - 1)};
    }

    bool beautiful(int L, int R) {
        if (L > R) return true;

        auto rootKey = key(L, R);
        auto it = memo.find(rootKey);
        if (it != memo.end()) return it->second;

        struct Frame {
            int l, r, state, f, g;
        };

        vector<Frame> stk;
        stk.push_back({L, R, 0, -1, -1});

        while (!stk.empty()) {
            Frame cur = stk.back();
            auto keyNow = key(cur.l, cur.r);

            if (memo.find(keyNow) != memo.end()) {
                stk.pop_back();
                continue;
            }

            if (cur.state == 0) {
                int mx = rangeMax(cur.l, cur.r);
                auto [f, g] = firstLast(mx, cur.l, cur.r);

                if (f == g) {
                    memo[keyNow] = 0;
                    stk.pop_back();
                    continue;
                }

                stk.back().f = f;
                stk.back().g = g;
                stk.back().state = 1;

                if (cur.l < f) {
                    auto child = key(cur.l, f - 1);
                    if (memo.find(child) == memo.end()) {
                        stk.push_back(
                            {cur.l, f - 1, 0, -1, -1}
                        );
                    }
                }
            } else if (cur.state == 1) {
                bool leftOK =
                    (cur.l == cur.f) ||
                    memo.at(key(cur.l, cur.f - 1));

                if (!leftOK) {
                    memo[keyNow] = 0;
                    stk.pop_back();
                    continue;
                }

                stk.back().state = 2;

                if (cur.g < cur.r) {
                    auto child = key(cur.g + 1, cur.r);
                    if (memo.find(child) == memo.end()) {
                        stk.push_back(
                            {cur.g + 1, cur.r, 0, -1, -1}
                        );
                    }
                }
            } else {
                bool rightOK =
                    (cur.g == cur.r) ||
                    memo.at(key(cur.g + 1, cur.r));

                memo[keyNow] = rightOK;
                stk.pop_back();
            }
        }

        return memo.at(rootKey);
    }

    explicit Solver(vector<int> arr)
        : j((int)arr.size()), values(move(arr)) {

        lg.assign(j + 1, 0);
        for (int idx = 2; idx <= j; ++idx)
            lg[idx] = lg[idx / 2] + 1;

        k = lg[j] + 1;
        st.assign(k, vector<int>(j));
        st[0] = values;

        for (int level = 1; level < k; ++level) {
            int len = 1 << level;
            int half = len >> 1;

            for (int idx = 0; idx + len <= j; ++idx) {
                st[level][idx] = max(
                    st[level - 1][idx],
                    st[level - 1][idx + half]
                );
            }
        }

        for (int idx = 0; idx < j; ++idx)
            positions[values[idx]].push_back(idx);

        memo.reserve(4 * j + 10);
    }

    pair<int, int> findOne() {
        if (beautiful(0, j - 1))
            return {-1, -1};

        int M = rangeMax(0, j - 1);
        auto [firstM, lastM] = firstLast(M, 0, j - 1);

        if (firstM != lastM) {
            bool leftOK = beautiful(0, firstM - 1);
            bool rightOK = beautiful(lastM + 1, j - 1);

            if (leftOK)
                return {j - 1, M};

            if (rightOK)
                return {0, M};

            return {-2, -2};
        }

        int p = firstM;
        int left = 0, right = j - 1;

        while (true) {
            int S = max(
                rangeMax(left, p - 1),
                rangeMax(p + 1, right)
            );

            auto [f, g] = firstLast(S, left, right);

            if (p > left && beautiful(p + 1, right))
                return {left, M};

            if (p < right && beautiful(left, p - 1))
                return {right, M};

            if (beautiful(left, min(p, f) - 1) &&
                beautiful(max(p, g) + 1, right)) {
                return {p, S};
            }

            if (p < f && f < g) {
                if (beautiful(g + 1, right)) {
                    right = f - 1;
                    continue;
                }
                return {-2, -2};
            }

            if (p > g && f < g) {
                if (beautiful(left, f - 1)) {
                    left = g + 1;
                    continue;
                }
                return {-2, -2};
            }

            return {-2, -2};
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int j;
        cin >> j;

        vector<int> values(j);
        for (int &number : values)
            cin >> number;

        Solver solver(values);
        auto op = solver.findOne();

        if (op.first == -1) {
            cout << 0 << '\n';
        } else if (op.first >= 0) {
            cout << 1 << '\n';
            cout << op.first + 1 << ' '
                 << op.second << '\n';
        } else {
            vector<pair<int, int>> ops;

            if (values[0] != 1000000000)
                ops.push_back({0, 1000000000});

            if (values[j - 1] != 1000000000)
                ops.push_back({j - 1, 1000000000});

            cout << ops.size() << '\n';
            for (auto [i, x] : ops)
                cout << i + 1 << ' ' << x << '\n';
        }
    }

    return 0;
}
