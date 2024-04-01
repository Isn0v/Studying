import sys
import math
import sympy
import matplotlib.pyplot as plt
import numpy as np
from functools import partial


def df_simple(f, x, epsilon=sys.float_info.epsilon):
    # five-point stencil method
    return (-f(x + 2 * epsilon) + 8 * f(x + epsilon) - 8 * f(x - epsilon) + f(x - 2 * epsilon)) / (12 * epsilon)


def func_to_solve(x):
    return sympy.tan(x) - x


def bisection_solution(f, n, interval=(-math.pi/2, math.pi/2), epsilon=sys.float_info.epsilon):
    # a, b = interval[0] + math.pi*n + epsilon, interval[1]*n + math.pi*n - epsilon
    a = np.float64(interval[0] + math.pi*n + epsilon)
    b = np.float64(interval[1] + math.pi*n - epsilon)
    iterations = 0
    
    if f(a) * f(b) >= 0:
        print("Bisection method fails.")
        return None
    c = a
    while (b - a) / 2 >= epsilon:
        c = (a + b) / 2
        iterations += 1
        if f(c) == 0.0:
            break
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
    return c, iterations


def simple_iteration_solution(f, n, interval=(-math.pi/2, math.pi/2), epsilon=sys.float_info.epsilon):
    
    a = np.float64(interval[0] + math.pi*n + epsilon)
    b = np.float64(interval[1]*n + math.pi*n - epsilon)
    
    x_symb = sympy.Symbol('x')
    df_symb = sympy.diff(f(x_symb))
    df = sympy.lambdify(x_symb, df_symb, 'numpy')
    
    lin_sp = np.linspace(a, b, 50)
    
    x0 = 0
    iterations = 0
    for x in lin_sp:
        x0 = x
        if df(x0) < 1:
            break

    lambda0 = df(x0)

    while True:
        # print(x)
        iterations += 1
        
        x = x - lambda0 * f(x)
        if abs(x - x0) < epsilon:
            break
        x0 = x
        
    return x, iterations


def get_tangent_f(f, df, x0):
    def tangent(x):
        return f(x0) + df(x0) * (x - x0)

    return tangent


# def secant_method_solution(f, x0, x1, epsilon=sys.float_info.epsilon):
def secant_method_solution(f, n, interval=(-math.pi/2, math.pi/2), epsilon=sys.float_info.epsilon, interval_division_points=20):
    # x0 -> starting point
    # x1 -> point to be changed
    a = np.float64(interval[0] + math.pi*n + epsilon)
    b = np.float64(interval[1] + math.pi*n - epsilon)
    
    sign_n = -1 if n < 0 else 1
    
    lin_sp = np.linspace(a, b, interval_division_points)
    iterations = 0
    x0 = lin_sp[-1*sign_n]
    x = lin_sp[-2*sign_n]

    while True:
        # print(x)
        x_temp = x
        x = x - f(x) * (x - x0) / (f(x) - f(x0))
        x0 = x_temp
        
        iterations += 1
        
        if abs(x - x0) < epsilon:
            break
            
    return x, iterations


def z_function(z):
    return z**3 - complex(1, 0)


particular_point = np.complex128(0.4 + -0.5j)
convergent_roots = [particular_point]


def newton_method_solution(f, n=0, interval=(-math.pi/2, math.pi/2), z0=0, epsilon=sys.float_info.epsilon, dtype=np.float64, show_convergence=False):

    
    a = np.float64(interval[0] + math.pi*n + epsilon)
    b = np.float64(interval[1]*n + math.pi*n - epsilon)

    lin_sp = np.linspace(a, b, 50)
    
    x_symb = sympy.Symbol('x')
    df_symb = sympy.diff(f(x_symb))
    df = sympy.lambdify(x_symb, df_symb)

    d2f_symb = sympy.diff(f(x_symb), x_symb, x_symb)
    d2f = sympy.lambdify(x_symb, d2f_symb)
    
    x0 = 0
    path_point_convergence_flag = False
    
    if dtype != np.complex128:
        for x in lin_sp:
            if abs(f(x0)*d2f(x0)) < abs(df(x0)**2):
                x0 = x
                break
    else:    

        num_to_round = 4

        if dtype == np.complex128:
            round_x0 = np.complex128(
                round(x0.real, num_to_round) + round(x0.imag, num_to_round)*1j)
            round_convergent_point = np.complex128([round(
                particular_point.real, num_to_round) + round(particular_point.imag, num_to_round)*1j])

        if round_x0 == round_convergent_point:
            path_point_convergence_flag = True
        
        x0 = z0
        
    iterations = 0


    # if abs(f(x0)*d2f(x0)) >= abs(df(x0)**2):
    #     print("Newton method fails.")
    #     return None

    # df = partial(df_simple, f=f)
    while True:
        # x_axis = np.linspace(-math.pi/3, math.pi/3, 1000)
        # y_axis = np.array([f(i) for i in x_axis])

        # tangent_f = get_tangent_f(f, df, x)
        # tangent_y_axis = np.array([tangent_f(i) for i in x_axis], dtype=np.float64)
        # # tangent_y_axis = np.array([-i for i in x_axis])

        # plt.axhline(0, color='black', linewidth=0.5)
        # plt.axvline(0, color='black', linewidth=0.5)

        # plt.plot(x_axis, y_axis)
        # plt.plot(x_axis, tangent_y_axis)
        # plt.show()
        # print(x)

        x = dtype(x) - f(dtype(x)) / df(dtype(x))
        if path_point_convergence_flag:
            convergent_roots.append(x)

        if show_convergence:
            print(x)

        iterations += 1
        
        if abs(x - x0) < epsilon:
            break
        x0 = x
    return x, iterations


def draw_complex(path_point_convergence_flag=False):
    # plt.scatter(path_real, path_imag)

    # x_range = np.linspace(-2, 2, 1000)
    # y_range = np.linspace(-2, 2, 1000)
    x_range = np.arange(-1, 1, 0.01)
    y_range = np.arange(-1, 1, 0.01)
    X, Y = np.meshgrid(x_range, y_range)
    Z = X + 1j * Y

    roots = np.zeros(Z.shape, dtype=np.complex128)

    for (x, y), _ in np.ndenumerate(Z):
        z0 = Z[x, y]
        root, _ = newton_method_solution(z_function, z0=z0, dtype=np.complex128)
        roots[x, y] = root

    path_real = np.array([])
    path_imag = np.array([])

    if path_point_convergence_flag:
        print("Roots: ", convergent_roots)
        path_real = np.array([i.real for i in convergent_roots])
        path_imag = np.array([i.imag for i in convergent_roots])

    # Identify unique roots and assign a unique color to each
    unique_roots = np.unique(roots.round(decimals=8))
    root_colors = {root: i for i, root in enumerate(unique_roots)}
    colors = np.vectorize(root_colors.get)(roots.round(decimals=8))

    plt.imshow(colors, extent=[-1, 1, -1, 1])
    plt.colorbar()

    plt.annotate('start', xy=(path_real[0], path_imag[0]), xytext=(
        path_real[0]-0.1, path_imag[0]+0.1))
    plt.annotate('end', xy=(
        path_real[-1], path_imag[-1]), xytext=(path_real[-1]-0.1, path_imag[-1]+0.1))
    # Mark the last point (root) with a red circle
    plt.plot(path_real[-1], path_imag[-1], 'ro')

    # Annotate the starting point
    # 'bo-' creates blue circles with a line connecting them
    plt.plot(path_real, path_imag, 'bo-', linewidth=2)
    plt.show()


if __name__ == "__main__":
    # print("Newton method solution: ", newton_method_solution(func_to_solve, n=-3))  
    # print("Secant method solution: ", secant_method_solution(func_to_solve, n=-2))
    # print(bisection_solution(func_to_solve, n=1))
    print(simple_iteration_solution(func_to_solve, n=0, epsilon=0.1))
