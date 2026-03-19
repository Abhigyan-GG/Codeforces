#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 1e9 + 9;

void solve(){
    ll a, b, c, m; cin >> a >> b >> c >> m;
    ll A = m/a, B = m/b, C = m/c;
    ll AB = m/lcm(a, b), BC = m/lcm(b, c), CA = m/lcm(c, a);
    ll ABC = m/lcm(a, lcm(b, c));
    AB -= ABC; BC -= ABC; CA -= ABC;
    A -= (AB + CA + ABC); B -= (AB + BC + ABC); C -= (BC + CA + ABC);
    cout << A*6 + (AB + CA) * 3 + ABC * 2 << " ";
    cout << B*6 + (AB + BC) * 3 + ABC * 2 << " ";
    cout << C*6 + (BC + CA) * 3 + ABC * 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t; cin >> t;
    while (t--) solve();
}