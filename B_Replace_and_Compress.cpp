#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string text;
        cin >> text;

        int length = static_cast<int>(text.size());
        bool repeatedMiddle = false;
        bool changedMiddle = false;

        for (int position = 1; position + 1 < length; ++position) {
            if (text[position - 1] != text[position + 1]) {
                continue;
            }

            if (text[position]== text[position - 1]) {
                repeatedMiddle =true;
            } else {
                changedMiddle = true;
            }
        }

        int answer = 1;
        if (repeatedMiddle) {
            ++answer;
        }
        if (changedMiddle) {
            ++answer;
        }

        cout << answer<<'\n';
    }

    return 0;
}