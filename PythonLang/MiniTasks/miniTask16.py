import numpy as np
import time
from random import randint


ITERATIONS = 128

HEIGHT = 64
WIDTH = 64


def get_neighboors(field, col, row):
    if col - 1 < 0:
        a_up = field[col+1]
    elif col + 1 >= HEIGHT:
        a_up = field[col-1]
    else:
        a_up = field[col-1:col+2:2]

    b, res_b, a = field[col], [], []

    if row - 1 < 0:
        a = a_up[row: row + 2]
        res_b.append(b[row + 1])
    elif row + 1 == WIDTH:
        a = a_up[row - 1: row + 1]
        res_b.append(b[row - 1])
    else:
        a = a_up[row-1:row+2]
        res_b = b[row-1: row + 2:2]
    
    a.extend(res_b)
    return a

def get_neighboors_np(field, col, row):
    a = field[col-1:col+2:2, row-1:row+2]
    b = field[col, row-1:row+2]
    return np.concatenate((a, b), axis=None)

def run_frame(field):
    for col in range(HEIGHT):
        for row in range(WIDTH):
            neighboors = get_neighboors(field, col, row)
            if not field[col][row]:
                if neighboors.count(0) == 3:
                    field[col][row] = 1
            else:
                if neighboors.count(0) < 2 or neighboors.count(0) > 3:
                    field[col][row] = 0

def run_frame_np(field):
    for col in range(HEIGHT):
        for row in range(WIDTH):
            neighboors = get_neighboors_np(field, col, row)
            if not field[col, row]:
                if np.count_nonzero(neighboors) == 3:
                    field[col, row] = 1
            else:
                if np.count_nonzero(neighboors) < 2 or np.count_nonzero(neighboors) > 3:
                    field[col, row] = 0


field = [[randint(0, 1) for i in range(WIDTH)] for j in range(HEIGHT)]
np_field = np.array(field, dtype=int)

start = time.time()
for frame in range(ITERATIONS):
    if np.any(np_field):
        run_frame_np(np_field)
end = time.time()
delta_np = (end - start)

start = time.time()
for frame in range(ITERATIONS):
    if any(any(row) for row in field):
        run_frame(field)
end = time.time()

delta = end - start
print(delta - delta_np)