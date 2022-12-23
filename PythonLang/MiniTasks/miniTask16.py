import numpy as np
from random import randint


ITERATIONS = 128

HEIGHT = 8
WIDTH = 8

def get_neighboors(field, col, row):
    a = field[col-1:col+2:2, row-1:row+2]
    b = field[col, row-1:row+2:2]
    return np.concatenate((a, b), axis=None)

def run_frame(field):
    for col in range(HEIGHT):
        for row in range(WIDTH):
            neighboors = get_neighboors(field, col, row)
            if not field[col][row]:
                if np.count_nonzero(neighboors) == 3:
                    field[col][row] = 1
            else:
                if np.count_nonzero(neighboors) < 2 or np.count_nonzero(neighboors) > 3:
                    field[col][row] = 0

field = np.array([[randint(0, 1) for i in range(WIDTH)] for j in range(HEIGHT)], dtype=int)

print(field)
for frame in range(ITERATIONS):
    if np.any(field):
        run_frame(field)
print()
print(field)