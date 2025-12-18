import sys
from decimal import Decimal, getcontext

getcontext().prec = 80
input = sys.stdin.readline

n, k = map(int, input().split())

cnt = [0] * 101
for x in map(int, input().split()):
    cnt[x] += 1

pw1 = [[Decimal(1)] * (k + 1) for _ in range(101)]
pw0 = [[Decimal(1)] * (k + 1) for _ in range(101)]

for i in range(101):
    pi = Decimal(i) / Decimal(100)
    qi = Decimal(1) - pi
    for j in range(1, k + 1):
        pw1[i][j] = pw1[i][j - 1] * pi
        pw0[i][j] = pw0[i][j - 1] * qi

q = [[Decimal(0)] * (k + 1) for _ in range(k + 1)]

for w in range(k + 1):
    for l in range(k + 1 - w):
        num = Decimal(0)
        den = Decimal(0)
        for i in range(101):
            if cnt[i]:
                v = pw1[i][w] * pw0[i][l] * cnt[i]
                den += v
                num += (Decimal(i) / Decimal(100)) * v
        q[w][l] = Decimal(0) if den == 0 else num / den

dp = [[[None] * (k + 1) for _ in range(k + 1)] for __ in range(k + 1)]

def solve(w, l, t):
    if t == 0:
        return Decimal(1)
    if dp[w][l][t] is not None:
        return dp[w][l][t]

    p = q[w][l]

    bet = p * Decimal(2) * solve(w + 1, l, t - 1)
    obs = p * solve(w + 1, l, t - 1) + (Decimal(1) - p) * solve(w, l + 1, t - 1)

    dp[w][l][t] = bet if bet > obs else obs
    return dp[w][l][t]

res = Decimal(1000) * (solve(0, 0, k) - Decimal(1))

# Exact formatting
if res == res.to_integral():
    print(res.to_integral())
else:
    print(res.normalize())