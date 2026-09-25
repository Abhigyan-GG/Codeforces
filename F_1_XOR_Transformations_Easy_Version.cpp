#include <bits/stdc++.h>
using namespace std;

vector<int> transform(const vector<int>& a) {
    int n = a.size();

    vector<int> v;
    v.reserve(1LL * n * (n - 1) / 2);

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            v.push_back(a[i] ^ a[j]);

    nth_element(v.begin(), v.begin() + n, v.end());
    v.resize(n);
    sort(v.begin(), v.end());

    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n);
        for (int &x : a)
            cin >> x;

        sort(a.begin(), a.end());

        vector<unsigned int> queries(q);
        unsigned int mx = 0;

        for (auto &x : queries) {
            cin >> x;
            mx = max(mx, x);
        }

        vector<vector<int>> states;
        states.push_back(a);

        int cycleStart = -1;

        while ((unsigned long long)states.size() - 1 <= mx) {
            vector<int> nxt = transform(states.back());

            int found = -1;

            for (int i = 0; i < (int)states.size(); ++i) {
                if (states[i] == nxt) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                cycleStart = found;
                break;
            }

            states.push_back(move(nxt));
        }

        for (unsigned int x : queries) {
            unsigned long long idx;

            if (x < states.size()) {
                idx = x;
            } else {
                unsigned long long start = cycleStart;
                unsigned long long len = states.size() - cycleStart;
                idx = start + (x - start) % len;
            }

            cout << states[idx].back() - states[idx].front() << '\n';
        }
    }

    return 0;
}