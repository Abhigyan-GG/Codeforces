import sys

input = sys.stdin.readline
INF = 10**15

t = int(input())
out = []

for _ in range(t):
    x = input().strip()
    y = input().strip()

    dp0, dp1 = 0, INF

    for xi, yi in zip(x, y):
        xi = xi == '1'
        yi = yi == '1'

        a = dp0 + (yi) + (xi)
        b = dp1 + (yi) + (not xi)
        ndp0 = a if a < b else b

        a = dp0 + (not yi) + (not xi)
        b = dp1 + (not yi) + (xi)
        ndp1 = a if a < b else b

        dp0, dp1 = ndp0, ndp1

    out.append(str(dp0 if dp0 < dp1 else dp1))

print("\n".join(out))