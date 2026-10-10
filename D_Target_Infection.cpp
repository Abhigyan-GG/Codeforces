#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll LIM = 1000000000000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int j;
        ll m, k;
        cin >> j >> m >> k;

        map<ll, ll> events;
        events[1] = 0;
        events[LIM + 1] = 0;

        ll covered = 0;

        auto markRange = [&](ll left, ll right, ll change) {
            left = max(left, 1LL);
            right = min(right, LIM);

            if (left > right) {
                return;
            }

            events[left] += change;
            events[right + 1] -= change;
        };

        for (int index = 0; index < j; ++index) {
            ll left, right;
            cin >> left >> right;

            ll start = max(left, 1LL);
            ll finish = min(right, m);

            if (start <= finish) {
                covered += finish - start + 1;
            }

            markRange(left - m, right - m, 1);
            markRange(left, right, -1);
        }

        ll pos = 1;
        ll cur = covered;
        ll slope = events[1];
        ll ans = -1;

        auto it = events.upper_bound(1);

        while (it != events.end()) {
            ll x = it->first;
            ll right = min(x, LIM);
            ll len = right - pos;

            if (slope == 0) {
                if (cur == k) {
                    ans = pos;
                    break;
                }
            } else {
                ll d = k - cur;

                if (d % slope == 0) {
                    ll step = d / slope;

                    if (step >= 0 && step <= len) {
                        ans = pos + step;
                        break;
                    }
                }
            }

            if (x > LIM)
                break;

            cur += slope * (x - pos);
            pos = x;
            slope += it->second;
            ++it;
        }

        cout << ans << '\n';
    }

    return 0;
}