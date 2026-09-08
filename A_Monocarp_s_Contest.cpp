#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int interiorZeros = 0;

        // Count zeros only between the first and last elements
        for (int i = 1; i < n - 1; i++) {
            if (a[i] == 0) {
                interiorZeros++;
            }
        }

        // Both endpoints are already easy
        if (a[0] == 0 && a[n - 1] == 0) {
            cout << 0 << '\n';
        }
        // Both endpoints are hard
        else if (a[0] == 1 && a[n - 1] == 1) {
            if (interiorZeros >= 2)
                cout << 2 << '\n';
            else
                cout << -1 << '\n';
        }
        // Exactly one endpoint is hard
        else {
            if (interiorZeros >= 1)
                cout << 1 << '\n';
            else
                cout << -1 << '\n';
        }
    }

    return 0;
}