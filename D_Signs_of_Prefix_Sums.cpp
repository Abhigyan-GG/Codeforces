#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Interval { ll lo, hi; };

static vector<Interval> curState, nextState, mergeBuf;

static bool feasible(const string &s, ll k) {
    curState.clear();
    curState.push_back({0, 0});

    for (char ch : s) {
        nextState.clear();

        for (const Interval &pr : curState) {
            if (pr.lo == pr.hi) {
                ll v = pr.lo;
                if (ch == '0') {
                    if (v != 0 && llabs(v) <= k) nextState.push_back({0, 0});
                } else if (k >= 1) {
                    auto addClippedSide = [&](ll a, ll b) {
                        if (a > b) return;
                        if (ch == '+') a = max(a, 1LL);
                        else            b = min(b, -1LL);
                        if (a <= b) nextState.push_back({a, b});
                    };
                    addClippedSide(v - k, v - 1);
                    addClippedSide(v + 1, v + k);
                }
            } else {
                ll a = pr.lo - k, b = pr.hi + k;
                if (ch == '0') {
                    if (a <= 0 && 0 <= b) nextState.push_back({0, 0});
                } else if (ch == '+') {
                    a = max(a, 1LL);
                    if (a <= b) nextState.push_back({a, b});
                } else {
                    b = min(b, -1LL);
                    if (a <= b) nextState.push_back({a, b});
                }
            }
        }

        if (nextState.empty()) return false;

        sort(nextState.begin(), nextState.end(),
             [](const Interval &x, const Interval &y) { return x.lo < y.lo; });

        mergeBuf.clear();
        mergeBuf.push_back(nextState[0]);
        for (size_t j = 1; j < nextState.size(); j++) {
            if (nextState[j].lo <= mergeBuf.back().hi + 1)
                mergeBuf.back().hi = max(mergeBuf.back().hi, nextState[j].hi);
            else
                mergeBuf.push_back(nextState[j]);
        }
        swap(curState, mergeBuf);
    }
    return true;
}

static int solve(const string &s) {
    ll lo = 0, hi = (ll)s.size() + 2;
    if (!feasible(s, hi)) return -1;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (feasible(s, mid)) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    curState.reserve(1 << 12);
    nextState.reserve(1 << 12);
    mergeBuf.reserve(1 << 12);

    string s;
    while (t--) {
        int n;
        cin >> n >> s;
        cout << solve(s) << '\n';
    }
    return 0;
}