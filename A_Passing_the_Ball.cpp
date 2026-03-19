#include <bits/stdc++.h>
using namespace std; 

using ll = long long;

constexpr ll mod = 1e9 + 9;

void solve() {
    int n;
    cin >> n;
    string s; cin >> s;
    vector<ll> vis(n);
    ll idx = 0; vis[idx] = true;
    for(ll i = 0; i < n; i++) {
        if(s[i] == 'L') idx--;
        else idx++;
        if(vis[idx]) break;
        vis[idx] = true;
    }
    cout << accumulate(vis.begin(), vis.end(), 0LL) << "\n";
}

int main(){ 
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ll t; cin >> t;
    while(t--) solve();
}
