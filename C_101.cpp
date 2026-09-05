#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int &x : a)
        cin >> x;

    vector<int> ones;

    for (int i = 0; i < n; ++i) {
        if (a[i] == 1)
            ones.push_back(i);
    }

    int L = -1, R = -1;

    // ----------------------------------------
    // Case 1: there are existing 1s
    // ----------------------------------------
    if (!ones.empty()) {

        // Best interval between consecutive 1s
        for (int i = 1; i < (int)ones.size(); ++i) {
            int l = ones[i - 1];
            int r = ones[i];

            if (L == -1 || r - l > R - L) {
                L = l;
                R = r;
            }
        }

        // Try extending left of the first 1
        int first = ones.front();

        for (int i = 0; i < first; ++i) {
            if (a[i] == -1) {
                if (L == -1 || first - i > R - L) {
                    L = i;
                    R = first;
                }
                break;
            }
        }

        // Try extending right of the last 1
        int last = ones.back();

        for (int i = n - 1; i > last; --i) {
            if (a[i] == -1) {
                if (L == -1 || i - last > R - L) {
                    L = last;
                    R = i;
                }
                break;
            }
        }
    }

    // ----------------------------------------
    // Case 2: no existing 1s
    // ----------------------------------------
    else {
        int first = -1;
        int last = -1;

        for (int i = 0; i < n; ++i) {
            if (a[i] == -1) {
                if (first == -1)
                    first = i;

                last = i;
            }
        }

        if (first != -1) {
            // At least two -1s
            if (first != last) {
                L = first;
                R = last;
            }
            // Exactly one -1
            else {
                L = R = first;
            }
        }
    }

    // ----------------------------------------
    // Construct the optimal array
    // ----------------------------------------

    if (L != -1) {

        // Endpoints are 1
        a[L] = 1;
        a[R] = 1;

        // Everything inside is 0
        for (int i = L + 1; i < R; ++i) {
            if (a[i] == -1)
                a[i] = 0;
        }
    }

    // Remaining -1s can safely become 0
    for (int &x : a) {
        if (x == -1)
            x = 0;
    }

    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}