def extend_num_string(num, stop_val):
    res_val = ""
    for i in range(len(num), stop_val):
        res_val += "0"
    return res_val + str(num)


def normallize(a_str, b_str):
    max_len = max(len(a_str), len(b_str))

    if max_len == 1:
        return a_str, b_str

    if max_len % 2:
        max_len += 1


    if len(a_str) < max_len:
        a_str = extend_num_string(a_str, max_len)
    if len(b_str) < max_len:
        b_str = extend_num_string(b_str, max_len)
    return a_str, b_str


def run_alg(a_str, b_str):
    if len(a_str) == 1 and len(b_str) == 1:
        return int(a_str) * int(b_str)
    else:
        a_str, b_str = normallize(a_str, b_str)

        a = a_str[:len(a_str) // 2]
        b = a_str[len(a_str) // 2:]
        c = b_str[:len(b_str) // 2]
        d = b_str[len(b_str) // 2:]

        a_b, c_d = normallize(str(int(a) + int(b)), str(int(c) + int(d)))

        a_c = run_alg(a, c)
        b_d = run_alg(b, d)
        
        ab_cd = run_alg(a_b, c_d)

        sub_res = ab_cd - a_c - b_d

        a_c *= 10**len(a_str)
        sub_res *= 10**(len(a_str) // 2)
        return a_c + b_d + sub_res

if __name__ == "__main__":
    a, b = input().split()
    a, b = normallize(a, b)

    print(run_alg(a, b))  