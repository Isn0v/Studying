import numpy as np

with open("Algorithms and Structures\miniTask9\data.data", mode='w', encoding="utf-8") as f:
    for i in range(3, 11):
        for two in range(2):
            matrix = np.random.randint(100, size=(i, i))
            for lst in matrix:
                f.write(str(lst)[1:-1] + '\n')
            f.write('\n')

