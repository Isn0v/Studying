import sys, math, sympy
import matplotlib.pyplot as plt
import numpy as np
from functools import partial

def df_simple(f, x, epsilon=sys.float_info.epsilon):
    #five-point stencil method
    return (-f(x + 2 * epsilon) + 8 * f(x + epsilon) - 8 * f(x - epsilon) + f(x - 2 * epsilon)) / (12 * epsilon)

def func_to_solve(x):
    return sympy.tan(x) - x

def bisection_solution(f, a, b, epsilon=sys.float_info.epsilon):
    if f(a) * f(b) >= 0:
        print("Bisection method fails.")
        return None
    c = a
    while (b - a) / 2 >= epsilon:
        c = (a + b) / 2
        if f(c) == 0.0:
            break
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
    return c

def simple_iteration_solution(f, x0, epsilon=sys.float_info.epsilon):
    x = np.float64(x0)
    
    x_symb = sympy.Symbol('x')
    df_symb = sympy.diff(f(x_symb))
    df = sympy.lambdify(x_symb, df_symb, 'numpy')
    if df(x0) >= 1:
        print("Simple iteration method fails.")
        return None
    
    lambda0 = df(x0)
    
    while True:
        print(x)
        x = x - lambda0 * f(x)
        if abs(x - x0) < epsilon:
            break
        x0 = x
    return x

def get_tangent_f(f, df, x0):
    def tangent(x):
        return f(x0) + df(x0) * (x - x0)
    
    return tangent

def newton_method_solution(f, x0, epsilon=sys.float_info.epsilon):
    x = np.float64(x0)
    
    x_symb = sympy.Symbol('x')
    df_symb = sympy.diff(f(x_symb))
    d2f_symb = sympy.diff(df_symb(x_symb))
    
    df = sympy.lambdify(x_symb, df_symb, 'numpy')
    d2f = sympy.lambdify(x_symb, d2f_symb, 'numpy')
    
    if abs(f(x0)*d2f(x0)) >= df(x0)**2:
        print("Newton method fails.")
        return None
        
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
        x = np.float64(x) - f(np.float64(x)) / df(np.float64(x))
        if abs(x - x0) < epsilon:
            break
        x0 = x
    return x


def secant_method_solution(f, x0, x1, epsilon=sys.float_info.epsilon):
    x = np.float64(x1)

    while True:
        # print(x)
        x_temp = x
        x = x - f(x) * (x - x0) / (f(x) - f(x0))
        x0 = x_temp
        if abs(x - x0) < epsilon:
            break
    return x






if __name__ == "__main__":
    
    # print(newton_method_solution(func_to_solve, np.float64(-7.8)))
    # print(bisection_solution(func_to_solve, np.float64(-4.6), np.float64(-4.4)))
    print(simple_iteration_solution(func_to_solve, np.float64(0.5)))
    # print(secant_method_solution(func_to_solve, np.float64(-4.6), np.float64(4.5)))
    pass
