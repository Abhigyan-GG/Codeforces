#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;

    while (t--) {
        int j, k;
        cin >> j >> k;

        if (j == 0 && k == 0) {
            cout << 0 << '\n';
        }
        else if (k <= j && (j - k) % 2 == 0) {
            cout << j << '\n';
        }
        else if (k <= j + 1 && (j + 1 - k) % 2 == 0) {
            cout << j + 1 << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }

    return 0;
}