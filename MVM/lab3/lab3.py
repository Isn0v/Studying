import numpy as np
import math
import matplotlib.pyplot as plt
from functools import reduce


# n from 3 to 10
# i from 0 to n


def get_default_Xi(i, n):
    return 2*i/n - 1

def get_chebyshev_Xi(i, n, interval=(-1, 1)):
    return (interval[0] + interval[1]) / 2 + (interval[1] - interval[0]) / 2 * math.cos((2*i + 1) / (2*n + 2) * math.pi)

def get_f_Xi(Xi):
    return 1 / (1 + 25* Xi**2)



def get_interpolation(n, Xi_func):
    global f_root_list
    f_root_list = []
    for i in range(0, n+1):
        Xi = Xi_func(i, n)
        f_Xi = get_f_Xi(Xi)
        f_root_list.append((f_Xi, Xi))
        
    def basic_polinom(i, x):
        p = [(x - f_root_list[j][1]) / (f_root_list[i][1] - f_root_list[j][1]) for j in range(0, n+1) if j != i]    
        return reduce(lambda x, y: x * y, p)
        
    def P(x):
        return sum ([f_root_list[i][0] * basic_polinom(i, x) for i in range(0, n+1)])
    
    return P




if __name__ == "__main__":
    for n in range(3, 11):
        P = get_interpolation(n, get_default_Xi)
        # P = get_interpolation(n, get_chebyshev_Xi)
        x = np.linspace(-1, 1, 10000)
        # y = [abs(P(i) - get_f_Xi(i)) for i in x]
        y = [P(i) for i in x]
        plt.plot(x, y, label="P_"+str(n)+"(x)")
        plt.legend()
        # plt.scatter([f_root_list[i][1] for i in range(0, n+1)], [f_root_list[i][0] for i in range(0, n+1)])
        
    plt.show()
        
        

