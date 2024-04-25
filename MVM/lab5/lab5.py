import numpy as np

def thomas_algorithm(a, b, c, d):
    n = len(d)
    cp = np.zeros(n-1)  
    dp = np.zeros(n)    

    cp[0] = c[0] / b[0]
    dp[0] = d[0] / b[0]

    for i in range(1, n-1):
        cp[i] = c[i] / (b[i] - a[i-1] * cp[i-1])

    for i in range(1, n):
        dp[i] = (d[i] - a[i-1] * dp[i-1]) / (b[i] - a[i-1] * cp[i-1])

    x = np.zeros(n)
    x[-1] = dp[-1]

    for i in reversed(range(n-1)):
        x[i] = dp[i] - cp[i] * x[i+1]

    return x





def solve_tridiagonal(N, a_val, b_val):
    h = np.pi / (N - 1)
    x = np.linspace(-np.pi/2, np.pi/2, N)
    a = np.ones(N-1)
    b = -2 * np.ones(N)
    c = np.ones(N-1)
    d = np.cos(x) * h**2

    b[0] = -1
    d[0] = h * a_val

    b[-1] = 1
    a[-1] = 0
    d[-1] = b_val

    y = thomas_algorithm(a, b, c, d)

    return x, y


N = 100
a_val = -1
b_val = -5

c_1 = a_val + 1
c_2 = b_val - c_1*np.pi/2

x_vals, y_vals = solve_tridiagonal(N, a_val, b_val)

import matplotlib.pyplot as plt

y_v = -np.cos(x_vals) + c_1*x_vals + c_2

plt.plot(x_vals, y_vals, label="Approximate Solution")
plt.plot(x_vals, y_v, label="Exact Solution")
# plt.plot(x_vals, abs(y_v - y_vals), label="")

plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()