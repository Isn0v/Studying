import numpy as np
import matplotlib.pyplot as plt
import math
import sympy
import sys
from functools import reduce


def get_interpolation(n, f_root_list):

    def basic_polinom(i, x):
        p = [(x - f_root_list[j][1]) / (f_root_list[i][1] - f_root_list[j][1])
             for j in range(0, n+1) if j != i]
        return reduce(lambda x, y: x * y, p)

    def P(x):
        return sum([f_root_list[i][0] * basic_polinom(i, x) for i in range(0, n+1)])

    return P


def func_a(x):
    return sympy.sin(math.pi * x**5)/(x**5*(1-x))


def func_b(x):
    return sympy.exp(-x**0.5+sympy.sin(x/10))


interval_for_a = (0, 1)
interval_for_b = (0, float('inf'))


def simpson_integral(f, interval, N_parts=1000):
    a, b = interval
    if a == 0:
        a = a + sys.float_info.epsilon
    if b == 1:
        b = b - sys.float_info.epsilon

    f_roots_list = [(f(a), a), (f((a+b)/2), (a+b)/2), (f(b), b)]
    
    # не понимаю зачем он нужен, если интеграл можно считать от изначальной функции
    p = get_interpolation(2, f_roots_list)

    x = sympy.Symbol('x')
    d_4 = sympy.diff(f(x), x, x, x, x)
    d_4f = sympy.lambdify(x, d_4)

    interval_array = np.linspace(a, b, N_parts)

    # отрсиовка функций для сравнения
    # f_interval_array = np.array([f(i) for i in interval_array])
    # p_interval_array = np.array([p(i) for i in interval_array])

    # plt.plot(interval_array, f_interval_array, label="f(x)")
    # plt.plot(interval_array, p_interval_array, label="p(x)")
    # plt.legend()

    h = (b - a) / N_parts

    f_for_int = f
    integral_result = h/3*(f_for_int(a) + 4*np.sum(np.array([f_for_int(interval_array[2*i - 1]) for i in range(1, N_parts//2)])) + 2*np.sum(
        np.array([f_for_int(interval_array[2*i]) for i in range(2, N_parts//2)])) + f_for_int(b))

    interval_array = np.linspace(a, b, 10000000)
    m_4 = np.max(np.absolute(d_4f(interval_array)))

    R = (b - a)*h**4*m_4/2880  # понятия не имею почему число такое большое

    plt.show()
    return integral_result, R


if __name__ == '__main__':
    # 1 интеграл
    res, R = simpson_integral(func_a, interval_for_a, N_parts=100000)
    print(res, R)

    # замена для 2 интеграла
    def x_t(t):
        return t/(1-t)

    def f_b_with_t(t):
        return func_b(x_t(t))/(1-t)**2

    # 2 интеграл
    res, R = simpson_integral(f_b_with_t, interval_for_a, N_parts=1000)
    print(res, R)
