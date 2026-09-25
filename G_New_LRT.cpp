#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

const ll MOD = 1000000007LL;

static inline ll powmod(ll a, ll e, ll m) {
    a %= m; if (a < 0) a += m;
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = (lll)r * a % m;
        a = (lll)a * a % m;
        e >>= 1;
    }
    return r;
}

struct NTT {
    ll mod, g;
    unordered_map<int, vector<int>> revCache;
    unordered_map<int, vector<ll>> rootCache;   // forward roots, indexed [size] -> array of size/2 (level-concatenated)
    unordered_map<int, vector<ll>> rootInvCache;

    NTT(ll mod_, ll g_): mod(mod_), g(g_) {}

    vector<int>& getRev(int n) {
        auto it = revCache.find(n);
        if (it != revCache.end()) return it->second;
        vector<int> rev(n);
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            rev[i] = j;
        }
        auto& ref = revCache[n];
        ref = move(rev);
        return ref;
    }

    // roots[len/2 .. len-1... ] we store per-level concatenated array of size n (like standard iterative NTT with precomputed roots)
    vector<ll>& getRoots(int n, bool invert) {
        auto& cache = invert ? rootInvCache : rootCache;
        auto it = cache.find(n);
        if (it != cache.end()) return it->second;
        vector<ll> roots(n);
        roots[0] = 1;
        for (int len = 2; len <= n; len <<= 1) {
            ll w = powmod(g, (mod - 1) / len, mod);
            if (invert) w = powmod(w, mod - 2, mod);
            ll wn = 1;
            for (int j = 0; j < len / 2; j++) {
                roots[len / 2 + j] = wn;
                wn = (lll)wn * w % mod;
            }
        }
        auto& ref = cache[n];
        ref = move(roots);
        return ref;
    }

    void ntt(vector<ll>& a, bool invert) {
        int n = a.size();
        vector<int>& rev = getRev(n);
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        vector<ll>& roots = getRoots(n, invert);
        for (int len = 2; len <= n; len <<= 1) {
            int half = len / 2;
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; j++) {
                    ll u = a[i + j];
                    ll v = (lll)a[i + j + half] * roots[half + j] % mod;
                    ll s = u + v; if (s >= mod) s -= mod;
                    ll d = u - v; if (d < 0) d += mod;
                    a[i + j] = s;
                    a[i + j + half] = d;
                }
            }
        }
        if (invert) {
            ll n_inv = powmod(n, mod - 2, mod);
            for (int i = 0; i < n; i++) a[i] = (lll)a[i] * n_inv % mod;
        }
    }

    vector<ll> multiply(vector<ll> a, vector<ll> b) {
        int rs = (int)a.size() + (int)b.size() - 1;
        int sz = 1;
        while (sz < rs) sz <<= 1;
        a.resize(sz); b.resize(sz);
        ntt(a, false); ntt(b, false);
        for (int i = 0; i < sz; i++) a[i] = (lll)a[i] * b[i] % mod;
        ntt(a, true);
        a.resize(max(rs,1));
        return a;
    }
};

NTT ntt1(998244353LL, 3);
NTT ntt2(1004535809LL, 3);
NTT ntt3(469762049LL, 3);

static inline ll crt_mod(ll r1, ll r2, ll r3) {
    const ll p1 = 998244353LL, p2 = 1004535809LL, p3 = 469762049LL;
    static const ll inv_p1_p2 = powmod(p1 % p2, p2 - 2, p2);
    ll t1 = (lll)(((r2 - r1) % p2 + p2) % p2) * inv_p1_p2 % p2;
    lll P1P2 = (lll)p1 * p2;
    lll X = (lll)r1 + (lll)p1 * t1;
    X %= P1P2; if (X < 0) X += P1P2;
    static const ll P1P2_mod_p3 = (ll)(((lll)p1 * p2) % p3);
    static const ll inv_P1P2_p3 = powmod(P1P2_mod_p3, p3 - 2, p3);
    ll X_mod_p3 = (ll)(X % p3);
    ll t2 = (lll)(((r3 - X_mod_p3) % p3 + p3) % p3) * inv_P1P2_p3 % p3;
    static const ll P1P2_mod_MOD = (ll)(((lll)p1 * p2) % MOD);
    ll X_mod_MOD = (ll)(X % MOD);
    ll ans = (X_mod_MOD + (lll)P1P2_mod_MOD * t2) % MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

vector<ll> multiply_mod(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> r1 = ntt1.multiply(a, b);
    vector<ll> r2 = ntt2.multiply(a, b);
    vector<ll> r3 = ntt3.multiply(a, b);
    int n = r1.size();
    vector<ll> res(n);
    for (int i = 0; i < n; i++) res[i] = crt_mod(r1[i], r2[i], r3[i]);
    return res;
}

vector<ll> poly_inverse(const vector<ll>& f, int n) {
    vector<ll> g(1, powmod(f[0], MOD - 2, MOD));
    int cur = 1;
    while (cur < n) {
        int nxt = cur * 2;
        vector<ll> fcut(f.begin(), f.begin() + min((int)f.size(), nxt));
        fcut.resize(nxt, 0);
        vector<ll> gg = g;
        gg.resize(nxt, 0);
        vector<ll> fg = multiply_mod(fcut, gg);
        fg.resize(nxt);
        vector<ll> tt(nxt, 0);
        tt[0] = (2 - fg[0] % MOD + MOD) % MOD;
        for (int i = 1; i < nxt; i++) tt[i] = (MOD - fg[i] % MOD) % MOD;
        vector<ll> newg = multiply_mod(gg, tt);
        newg.resize(nxt);
        g = move(newg);
        cur = nxt;
    }
    g.resize(n);
    return g;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll n, m;
        scanf("%lld %lld", &n, &m);
        vector<ll> c(m + 1);
        for (ll i = 1; i <= m; i++) scanf("%lld", &c[i]);

        int N = (int)n;
        vector<ll> D(N + 1, 0);
        D[0] = 1;
        for (int x = 1; x <= N; x++) {
            if ((x & m) == x) D[x] = MOD - 1;
        }
        vector<ll> G = poly_inverse(D, N + 1);
        vector<ll> G2 = multiply_mod(G, G);
        G2.resize(N + 1);
        vector<ll> B(N + 1, 0);
        for (int x = 1; x <= N && x <= m; x++) {
            if ((x & m) == x) B[x] = c[x] % MOD;
        }
        vector<ll> F = multiply_mod(B, G2);
        ll ans = (N < (int)F.size()) ? F[N] % MOD : 0;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}