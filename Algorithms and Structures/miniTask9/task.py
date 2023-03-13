import numpy as np
import time
import statistics

#--------------------->
#matrix operations
def sub_matrixes(matr):
        m = len(matr) // 2
        n = len(matr[0]) // 2

        a = matr[:m, :n]
        b = matr[:m, n:]
        c = matr[m:, :n]
        d = matr[m:, n:]
        return a, b, c, d
    
def change_len(matr):
    def find_degree(num): #degree of 2 higher then given num
        res = 1
        while True:
            if 2**res > num:
                return 2**res
            res += 1 


    m_old = len(matr)
    n_old = len(matr[0])

    m = find_degree(m_old)
    n = find_degree(n_old)

    max_len = max(m, n)

    new_matr = np.zeros((max_len, max_len))
    new_matr[:m_old, :n_old] = matr
    return new_matr

def mult_matrix_classic(matrixes): #m*k and k*n
    matrix1 = matrixes[0]
    matrix2 = matrixes[1]

    res_matr = [[0 for i in range(len(matrix2[0]))] for j in range(len(matrix1))]
    for i in range(len(matrix1)):
        for j in range(len(matrix2[0])):
            for k in range(len(matrix2)):
                res_matr[i][j] += matrix1[i][k] * matrix2[k][j]
    return res_matr

def mult_matrix_recursive(matrixes, resize=True):
    matrix1 = matrixes[0]
    matrix2 = matrixes[1]

    save_m = len(matrix1)
    save_n = len(matrix2[0])

    if resize:
        matrix1 = change_len(matrix1)
        matrix2 = change_len(matrix2)

    if np.shape(matrix1) == (1, 1) and np.shape(matrix2) == (1, 1):
        return np.array([matrix1[0, 0] * matrix2[0, 0]])

    a, b, c, d = sub_matrixes(matrix1)
    e, f, g, h = sub_matrixes(matrix2)

    a_e = mult_matrix_recursive((a, e), False)
    b_g = mult_matrix_recursive((b, g), False)
    c_e = mult_matrix_recursive((c, e), False)
    d_g = mult_matrix_recursive((d, g), False)
    a_f = mult_matrix_recursive((a, f), False)
    b_h = mult_matrix_recursive((b, h), False)
    c_f = mult_matrix_recursive((c, f), False)
    d_h = mult_matrix_recursive((d, h), False)

    ae_bg = a_e + b_g
    ce_dg = c_e + d_g
    af_bh = a_f + b_h
    cf_dh = c_f + d_h

    res_fhalf = np.vstack((ae_bg, ce_dg))
    res_shalf = np.vstack((af_bh, cf_dh))
    res_matr = np.hstack((res_fhalf, res_shalf))

    res_matr = res_matr[:save_m, :save_n]

    return res_matr

def shtrassen(matrixes, resize=True):
    matrix1 = matrixes[0]
    matrix2 = matrixes[1]

    save_m = len(matrix1)
    save_n = len(matrix2[0])

    if resize:
        matrix1 = change_len(matrix1)
        matrix2 = change_len(matrix2)

    if np.shape(matrix1) == (1, 1) and np.shape(matrix2) == (1, 1):
        return np.array([matrix1[0, 0] * matrix2[0, 0]])
    
    a11, a12, a21, a22 = sub_matrixes(matrix1)
    b11, b12, b21, b22 = sub_matrixes(matrix2)

    d0 = shtrassen(((a11 + a22), (b11 + b22)), False)
    d1 = shtrassen(((a12 - a22), (b21 + b22)), False)
    d2 = shtrassen(((a21 - a11), (b12 + b11)), False)

    h1 = shtrassen(((a11 + a12), b22), False)
    h2 = shtrassen(((a21 + a22), b11), False)

    v1 = shtrassen((a22, (b21 - b11)), False)
    v2 = shtrassen((a11, (b12 - b22)), False)

    f_q = d0 + d1 + v1 - h1
    s_q = v2 + h1
    th_q = v1 + h2
    l_q = d0 + d2 + v2 - h2

    res_fhalf = np.vstack((f_q, th_q))
    res_shalf = np.vstack((s_q, l_q))
    res_matr = np.hstack((res_fhalf, res_shalf))

    res_matr = res_matr[:save_m, :save_n]

    return res_matr
#----------------------<


#----------------
#table
def format_table(benchmarks: list, algos: list, results: list):

    max_width = 0
    tmp = [i for i in benchmarks]
    tmp.extend(algos)
    for i in results:
        tmp.extend(i)
    tmp.append("Benchmark")

    for st in tmp:
        max_width = max(max_width, len(str(st)))

    res_str = f"| Benchmark " + " "*(max_width - 9)

    for word in algos:
        res_str += f"| {word} " + " "*(max_width - len(word))

    res_str += "|\n"
    base_len = len(res_str) - 3
    res_str += "|" + "-"*base_len + "|\n"

    for lst in zip(benchmarks, results):
        res_str += f"| {lst[0]} " + " "*(max_width - len(str(lst[0])))
        for num in lst[1]:
            res_str += f"| {num} " + " "*(max_width - len(str(num)))
        res_str += "|\n"

    print(res_str)
#----------------


def test_algorithm(algorithm, data):
    start_time = time.time()
    algorithm(data)
    return time.time() - start_time

def massive_algorithm_test(algorithm, data, number_of_tests = 10):
    INFELICITY = 2 #seconds
    time_results = []
    time_delta_new = 0

    for i in range(number_of_tests):
        time_result = test_algorithm(algorithm, data)

        if i >= 1:
            time_delta_old = time_delta_new
            time_delta_new = abs(time_results[i - 1] - time_result)
            if time_delta_new <= time_delta_old + INFELICITY:
                time_results.append(time_result)
        else:
            time_results.append(time_result)
    return statistics.mean(time_results) #approximation

def benchmark(algorithms, data):
    benchmarks = [] #names
    times_for_benchmarks = []
    algorithm_names = [func.__name__ for func in algorithms]
    for i in range(0, len(data) - 1, 2):
        matrixes = (data[i], data[i + 1])
        times = []
        benchmarks.append(f"data_set{i // 2}")
        for algorithm in algorithms:
            time = massive_algorithm_test(algorithm, matrixes)
            times.append(time)
        times_for_benchmarks.append(times)
    format_table(benchmarks, algorithm_names, times_for_benchmarks)


if __name__ == "__main__":
    algorithms = [mult_matrix_classic, mult_matrix_recursive, shtrassen]
    cube = []
    with open("Algorithms and Structures\miniTask9\data.data", encoding="utf-8") as f:
        matrix = []
        for line in f:
            if line != '\n':
                lst = list(map(int, line.split()))
                matrix.append(lst)
            else:
                cube.append(np.array(matrix))
                matrix = []
    benchmark(algorithms, cube)
