#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include <set>
#include <iterator>
using namespace std;
typedef long long ll;

bool feasible(const vector<int>& a, ll k, ll s) {
    ll n = a.size();
    map<ll, ll> cnt;
    for (int x : a) cnt[x]++;
    ll used = 0;
    ll c = 0;                     
    ll mx = cnt.rbegin()->first;
    for (ll u = mx; u > k; u--) {
        auto itu = cnt.find(u);
        if (itu != cnt.end()) c += itu->second;
        while (c > 0 && c > n + 2 * s + k - u) {
            if (used >= s) return false;
            auto it = cnt.lower_bound(u);         
            ll x = it->first;
            if (x / 2 >= u) return false;       
            if (--it->second == 0) cnt.erase(it);
            cnt[x / 2] += 2;
            c--; used++;
        }
    }
  
    while (used < s) {
        auto it = cnt.begin();
        ll x = it->first;
        if (--it->second == 0) cnt.erase(it);
        cnt[x / 2] += 2;
        used++;
    }
    ll idx = 0;
    for (auto& [v, m] : cnt) {
        if (v > k + s + idx) return false;
        idx += m;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;

        ll lo = 0, hi = 1;
        while (!feasible(a, k, hi)) hi *= 2;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (feasible(a, k, mid)) hi = mid;
            else lo = mid + 1;
        }
        cout << n + 2 * lo << '\n';
    }
    return 0;
}