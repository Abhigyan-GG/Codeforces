#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
inline ll maxPower2Multiple(const ll &a) {return a&-a;}
inline ll prefixAnswer(const ll &a) {return maxPower2Multiple(a);}
inline bool isPerfect(const ll &a) {return a == maxPower2Multiple(a);}
 
int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        ll l, r;
        cin >> l >> r;
        ll both = 1LL<<60;
        while((both&l) == (both&r) && both > 0) {
            if(both&l) l -= both, r -= both;
            both >>= 1;
        }
        if(l and isPerfect(l+r+1))
            cout << 2LL*min(prefixAnswer(l), prefixAnswer(r+1LL))-1LL << endl;
        else if(l)
            cout << min(prefixAnswer(l), prefixAnswer(r+1LL))-1LL << endl;
        else
            cout << prefixAnswer(r+1LL)-1LL << endl;
    }
    return 0;
}