#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--  ) {
        int length, window;
        cin >> length >> window;

        vector<int> data(length);
        for (int &number : data) {
            cin >> number;
        }

        vector<int> prefix(length + 1);
        for (int pos = 1; pos <= length; ++pos) {
            prefix[pos] = (prefix[pos - 1] + data[pos - 1]) % window;
        }

        vector<int> seen(window);
        long long total = 0;

        for (int right = window + 1; right <= length; ++right) {
             ++seen[prefix[right - window - 1]];
            total +=seen[prefix[right]];
        }

        cout << total << '\n';
    }

    return 0;
}