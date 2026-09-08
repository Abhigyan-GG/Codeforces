#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long x, y;
        cin >> x >> y;

        long long s = x + y;
        long long a = 0;
        bool less = false;

        for (int i = 60; i >= 0; --i) {
            int xb = (x >> i) & 1;
            int sb = (s >> i) & 1;

            if (less) {
                if (sb) a |= (1LL << i);
            } else {
                if (xb && sb) {
                    a |= (1LL << i);
                } else if (xb && !sb) {
                    less = true;
                }
            }
        }

        cout << s << ' ' << x - a << '\n';
    }

    return 0;
}