#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int j, k;
        cin >> j >> k;

        vector<int> count(j + 1, 0);

        for (int value = 0; value < j; ++value) {
            int number;
            cin >> number;
            ++count[number];
        }

        bool possible = false;

        for (int mex = 0; mex <= j; ++mex) {
            if (count[mex] == 2 * k - 1) {
                possible = true;
                break;
            }

            if (count[mex] < 2 * k) {
                break;
            }
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }

    return 0;
}