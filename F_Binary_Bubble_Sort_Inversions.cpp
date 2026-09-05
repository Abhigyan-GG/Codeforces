#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int m = 0;

    for (int &x : a) {
        cin >> x;
        m += x;
    }

    string s;
    cin >> s;

    if (m == 0) {
        for (int i = 0; i <= n; ++i) {
            cout << 0 << (i == n ? '\n' : ' ');
        }
        return;
    }

    vector<int> pos;
    for (int i = 0; i < n; ++i) {
        if (a[i])
            pos.push_back(i);
    }

    vector<int> z(m + 1);

    z[0] = pos[0];

    for (int i = 1; i < m; ++i) {
        z[i] = pos[i] - pos[i - 1] - 1;
    }

    z[m] = n - pos[m - 1] - 1;

    vector<int> D(m);

    for (int i = 0; i < m; ++i)
        D[i] = z[i + 1];

    int head = 0;

    set<int> st;

    for (int i = 0; i < m; ++i) {
        if (D[i] > 0)
            st.insert(i);
    }

    long long inv = 0;

    for (int i = 1; i <= m; ++i) {
        inv += 1LL * i * z[i];
    }

    cout << inv;

    for (char op : s) {

        if (op == '1') {
            long long removed = (n - m) - z[0];
            inv -= removed;

            int oldHead = head;

            z[0] += D[oldHead];

            st.erase(oldHead);
            D[oldHead] = 0;

            head = (head + 1) % m;
        }

        else {


            if (!st.empty()) {

                int k;

                auto it = st.lower_bound(head);

                if (it != st.end()) {
                    k = *st.rbegin();

                    if (k < head)
                        k = *prev(st.end());
                } else {
                    k = *prev(st.end());
                }

                int onesCrossed =
                    ((k - head + m) % m) + 1;

                inv -= onesCrossed;

                D[k]--;

                if (D[k] == 0)
                    st.erase(k);

                z[0]++;
            }
        }

        cout << ' ' << inv;
    }

    cout << '\n';
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