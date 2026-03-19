#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 1e9 + 9;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll &i : a) cin >> i;
    ll mx = 0, ct = 0;
    for (ll i =0; i < n; i++) {
        if(mx <= a[i]) ct++, mx = a[i];
    }
    cout << ct << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t; cin >> t;
    while (t--) solve();
}


