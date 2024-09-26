import numpy as np
import matplotlib.pyplot as plt


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


def inverse_iteration(a, b, c, E_guess, tol=1e-8, max_iters=100):
    n = len(b)
    phi = np.random.rand(n)
    phi[0] = phi[-1] = 0
    phi /= np.linalg.norm(phi)

    shift = E_guess
    E_array = [E_guess]
    for i in range(max_iters):
        phi_new = thomas_algorithm(a, b, c, phi)

        shift_new = np.dot(phi_new, phi) / np.dot(phi_new, phi_new)
        
        
        E_array.append(shift_new)
        if np.abs(shift_new - shift) < tol:
            break

        shift = shift_new
        phi = phi_new
        print(abs(0.5 - shift))

    return shift_new, phi_new, E_array, i


def draw(x, y, label):
    plt.plot(x, y, label=label)


def solve_shredinger():
    N = 100000
    L = 10   
    x = np.linspace(-L / 2, L / 2, N)
    h = x[1] - x[0]

    
    V = 0.5 * x**2

    
    tol = 1e-8
    max_iters = 1000

    
    a = np.full(N-1, 1.0 / h**2) * (-1/2)
    b = np.full(N, 1.0 / h**2 + V)
    c = np.full(N-1, 1.0 / h**2) * (-1/2)
    
    b[0] = 1
    c[0] = 0
    b[N-1] = 1
    a[N-2] = 0


    
    E_guess = 0
    iters_used = 0
    E_approx, phi_approx, E_array, iters_used = inverse_iteration(a, b, c, E_guess, tol, max_iters)
    iters = [i for i in range(0, len(E_array))]
    # draw(x, phi_approx, "Energy eigenvalue: " + str(E_approx))
    # draw(iters, E_array, "Energy eigenvalue from 1")
    # print(E_array)
    # plt.legend(loc="upper right")
    # plt.show()
    # print(abs(E_approx - 0.5))
    # print("iters_used: ", iters_used)
    # print("E_approx: ", E_approx)
    # print("phi_approx: ", phi_approx)


if __name__ == "__main__":
    solve_shredinger()

