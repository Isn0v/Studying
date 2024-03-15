import numpy as np

epsillon32 = np.float32(1.1920928955078125e-07)
epsillon64 = np.float64(2.220446049250313e-16)

a = np.float32(1.0)
epsillon = a
i = 0

p32_min = 150
p32_max = 128
while (a / np.float32(2)) != a:
    a /= np.float32(2)
    i += 1
print(f"{a}, {i}")
