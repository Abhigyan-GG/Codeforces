#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for (auto &x : a) scanf("%d", &x);

        // MEX of any set built from `a` can never exceed n,
        // so only values 0..n matter. Clamp everything else into an
        // unused bucket at index n+1 (never read as a "small" value).
        vector<int> cnt(n + 2, 0);
        for (int x : a) {
            if (x <= n + 1) cnt[x]++;
        }

        int c0 = cnt[0];

        if (c0 == 0) {
            // value 0 never appears -> every set's mex is forced to 0
            printf("YES\n");
            string s(n, 'A');
            printf("%s\n", s.c_str());
            continue;
        }

        if (c0 == 1) {
            // only one set can ever hold the sole 0 -> mex values are
            // (0, 0, z>=1), which can never satisfy x+y>=z
            printf("NO\n");
            continue;
        }

        // c0 >= 2: M2 = largest t such that cnt[v] >= 2 for all v < t
        int M2 = 0;
        while (M2 <= n && cnt[M2] >= 2) M2++;

        vector<int> seen(M2, 0);
        string s(n, 'C');

        for (int i = 0; i < n; i++) {
            int v = a[i];
            if (v < M2) {
                seen[v]++;
                if (seen[v] == 1) s[i] = 'A';
                else if (seen[v] == 2) s[i] = 'B';
                else s[i] = (v == 0) ? 'A' : 'C'; // keep extra 0's away from C
            } else {
                s[i] = 'C';
            }
        }

        printf("YES\n%s\n", s.c_str());
    }
    return 0;
}