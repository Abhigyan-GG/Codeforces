#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n,q;
    scanf("%d %d", &n, &q);
    static char s[300005];
    scanf("%s", s+1);

    vector<ll> prefO(n+1,0), prefDiff(n+1,0);
    for(int i=1;i<=n;i++){
        prefO[i] = prefO[i-1] + (s[i]=='1'?1:0);
    }
    for(int i=1;i<=n;i++){
        ll d = 0;
        if(i>=1 && i<n) d = (s[i]!=s[i+1])?1:0;
        prefDiff[i] = prefDiff[i-1] + d;
    }

    string out;
    out.reserve(q*3);
    for(int i=0;i<q;i++){
        int l,r;
        scanf("%d %d", &l, &r);
        ll n0 = r-l+1;
        ll o = prefO[r]-prefO[l-1];
        ll z = n0-o;
        ll T = 0;
        if(r-1>=l) T = prefDiff[r-1]-prefDiff[l-1];
        if(s[l]!=s[r]) T+=1;
        ll b = T/2;
        ll c1 = (z+1)/2;
        ll c2 = (o+1)/2;
        ll c3 = b;
        ll rhs = n0-b;
        ll c4 = (rhs>0)?(rhs+2)/3:0;
        ll Bp = max(max(c1,c2), max(c3,c4));
        ll ans = 4*Bp - n0;
        out += to_string(ans);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
    return 0;
}