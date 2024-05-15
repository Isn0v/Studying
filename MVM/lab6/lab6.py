import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math


def rk4(ode_function, initial_value, time_step, time_span):
    time_points = [0]
    values = [initial_value]
    num_steps = int(time_span / time_step)
    for _ in range(num_steps):
        t = time_points[-1]
        y = values[-1]
        k1 = ode_function(t, y)
        k2 = ode_function(t + time_step / 2, y + time_step * k1 / 2)
        k3 = ode_function(t + time_step / 2, y + time_step * k2 / 2)
        k4 = ode_function(t + time_step, y + time_step * k3)
        next_value = y + (time_step / 6) * (k1 + 2*k2 + 2*k3 + k4)
        time_points.append(t + time_step)
        values.append(next_value)
    return time_points, values

def rk4_system(ode1, ode2, x0, y0, t0, tf, n):
    h = (tf - t0) / float(n)

    t_values = [t0]
    x_values = [x0]
    y_values = [y0]

    for i in range(1, n+1):
        t_prev = t_values[-1]
        x_prev = x_values[-1]
        y_prev = y_values[-1]

        k1x = h * ode1([x_prev, y_prev], t_prev)
        k1y = h * ode2([x_prev, y_prev], t_prev)

        k2x = h * ode1([x_prev + 0.5 * k1x, y_prev + 0.5 * k1y], t_prev + 0.5 * h)
        k2y = h * ode2([x_prev + 0.5 * k1x, y_prev + 0.5 * k1y], t_prev + 0.5 * h)

        k3x = h * ode1([x_prev + 0.5 * k2x, y_prev + 0.5 * k2y], t_prev + 0.5 * h)
        k3y = h * ode2([x_prev + 0.5 * k2x, y_prev + 0.5 * k2y], t_prev + 0.5 * h)

        k4x = h * ode1([x_prev + k3x, y_prev + k3y], t_prev + h)
        k4y = h * ode2([x_prev + k3x, y_prev + k3y], t_prev + h)

        x_next = x_prev + (k1x + 2*k2x + 2*k3x + k4x) / 6.0
        y_next = y_prev + (k1y + 2*k2y + 2*k3y + k4y) / 6.0

        x_values.append(x_next)
        y_values.append(y_next)
        t_values.append(t_prev + h)

    return t_values, x_values, y_values

def rk4_3d_system(ode1, ode2, ode3, x0, y0, z0, t0, tf, n):
    h = (tf - t0) / float(n)

    t_values = [t0]
    x_values = [x0]
    y_values = [y0]
    z_values = [z0]

    for i in range(1, n + 1):
        t_prev = t_values[-1]
        x_prev = x_values[-1]
        y_prev = y_values[-1]
        z_prev = z_values[-1]

        k1x = h * ode1([x_prev, y_prev, z_prev], t_prev)
        k1y = h * ode2([x_prev, y_prev, z_prev], t_prev)
        k1z = h * ode3([x_prev, y_prev, z_prev], t_prev)

        k2x = h * ode1([x_prev + 0.5 * k1x, y_prev + 0.5 * k1y, z_prev + 0.5 * k1z], t_prev + 0.5 * h)
        k2y = h * ode2([x_prev + 0.5 * k1x, y_prev + 0.5 * k1y, z_prev + 0.5 * k1z], t_prev + 0.5 * h)
        k2z = h * ode3([x_prev + 0.5 * k1x, y_prev + 0.5 * k1y, z_prev + 0.5 * k1z], t_prev + 0.5 * h)

        k3x = h * ode1([x_prev + 0.5 * k2x, y_prev + 0.5 * k2y, z_prev + 0.5 * k2z], t_prev + 0.5 * h)
        k3y = h * ode2([x_prev + 0.5 * k2x, y_prev + 0.5 * k2y, z_prev + 0.5 * k2z], t_prev + 0.5 * h)
        k3z = h * ode3([x_prev + 0.5 * k2x, y_prev + 0.5 * k2y, z_prev + 0.5 * k2z], t_prev + 0.5 * h)

        k4x = h * ode1([x_prev + k3x, y_prev + k3y, z_prev + k3z], t_prev + h)
        k4y = h * ode2([x_prev + k3x, y_prev + k3y, z_prev + k3z], t_prev + h)
        k4z = h * ode3([x_prev + k3x, y_prev + k3y, z_prev + k3z], t_prev + h)

        x_next = x_prev + (k1x + 2 * k2x + 2 * k3x + k4x) / 6.0
        y_next = y_prev + (k1y + 2 * k2y + 2 * k3y + k4y) / 6.0
        z_next = z_prev + (k1z + 2 * k2z + 2 * k3z + k4z) / 6.0

        x_values.append(x_next)
        y_values.append(y_next)
        z_values.append(z_next)
        t_values.append(t_prev + h)

    return t_values, x_values, y_values, z_values

def lorenz_x(x, y, z, sigma):
    return sigma * (y - x)

def lorenz_y(x, y, z, rho):
    return x * (rho - z) - y

def lorenz_z(x, y, z, beta):
    return x * y - beta * z

def third_task():
    sigma = 10
    beta = 8/3
    rho = 10 # variated

    def lorenz_x_wrapper(y, t):
        return lorenz_x(y[0], y[1], y[2], sigma)
    def lorenz_y_wrapper(y, t):
        return lorenz_y(y[0], y[1], y[2], rho)
    def lorenz_z_wrapper(y, t):
        return lorenz_z(y[0], y[1], y[2], beta)

    initaial_values = [10, 10, 10]
    
    time_points, x_values, y_values, z_values = rk4_3d_system(lorenz_x_wrapper, lorenz_y_wrapper, lorenz_z_wrapper, initaial_values[0], initaial_values[1], initaial_values[2], 0, 100, 1000)

    # plt.plot(time_points, x_values, label="x")
    # plt.plot(time_points, y_values, label="y")
    # plt.plot(time_points, z_values, label="z")
    # plt.legend()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    # ax.plot(x_values, y_values, z_values)
    ax.scatter(x_values, y_values, z_values, s=2)
    
    plt.show()

def lotka_volterra(predator_prey, t, a, b, c, d):
    x, y = predator_prey
    dxdt = a * x - b * x * y
    dydt = c * x * y - d * y
    return [dxdt, dydt]


def second_task():
    a = 10
    b = 2
    c = 2
    d = 10
    
    def lotka_volterra_wrapper(y, t, index):
        return lotka_volterra(y, t, a, b, c, d)[index]
    
    def lotka_volterra_1(y, t):
        return lotka_volterra_wrapper(y, t, 0)
    def lotka_volterra_2(y, t):
        return lotka_volterra_wrapper(y, t, 1)
    
    initaial_values = [5, 10]
    
    time_points, x_values, y_values = rk4_system(lotka_volterra_1, lotka_volterra_2, initaial_values[0], initaial_values[1], 0, 10, 1000)
    
    # plt.plot(time_points, x_values, label="prey")
    # plt.plot(time_points, y_values, label="predator")
    plt.plot(x_values, y_values, label="predator-prey")
    # plt.plot(y_values, x_values, label="predator-prey")
    plt.legend()
    
    plt.show()
    

def first_task():
    def f(t, y):
        return -y
    
    initial_value = 1
    
    def f_actual(y):
        return math.exp(-y)*math.exp(math.log(initial_value))
    
    
    time_points, values = rk4(f, initial_value, 0.1, 10)
    
    # print(time_points)
    # print(values)
    
    # for i in [0.1, 0.01]:
    #     time_points, values = rk4(f, initial_value, i, 10)
    #     print(abs(f_actual(time_points[-1]) - values[-1]))
    
    # plt.plot(time_points, values, label="rk4")
    # plt.plot(time_points, [f_actual(y) for y in time_points], label="actual")
    f_actual_arr = [f_actual(y) for y in time_points]
    plt.plot(time_points, [abs(values[i] - f_actual_arr[i])/f_actual_arr[i] for i in range(len(values))], label="error")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    # first_task()
    # second_task()
    third_task()