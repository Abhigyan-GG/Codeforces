#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<ll> a(n);

        for (auto &x : a)
            cin >> x;

        ll ans = 0;

        int leftMiddle = k - 1;
        int rightMiddle = n - k;

        if(leftMiddle <= rightMiddle){
            for(int i=leftMiddle;i<=rightMiddle;i++){
                ans += a[i];
            }
        }

        vector<ll> v;

        for (int i=0;i<n;i++) {
            if(i >= leftMiddle && i <= rightMiddle)
                continue;

            v.push_back(a[i]);
        }

        int remaining=n-k+1;

        if(leftMiddle <= rightMiddle)
        {
            remaining -= rightMiddle-leftMiddle+1;
        }

        int l = 0;
        int r=(int)v.size()-1;

        while(remaining--){
            ans += max(v[l], v[r]);
            ++l;
            --r;
        }

        cout << ans << '\n';
    }

    return 0;
}