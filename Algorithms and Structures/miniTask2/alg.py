def half_slice(num):
    l = int_len(num) 
    if l % 2:
        l = (l // 2) + 1
    else:
        l //= 2
    return num // (10 ** l), num % (10 ** l)

def int_len(num):
    if num == 0:
        return 1
    count = 0
    while num != 0:
        count += 1
        num //= 10
    return count

def run_alg(num, delim):
    if int_len(num) == 1 and int_len(delim) == 1:
        return num * delim
    else:

        a, b = half_slice(num)
        c, d = half_slice(delim)

        a_b = a + b
        c_d = c + d

        a_c = run_alg(a, c)
        b_d = run_alg(b, d)
        
        ab_cd = run_alg(a_b, c_d)

        sub_res = ab_cd - a_c - b_d

        l = max(int_len(num), int_len(delim))
        h_l = l // 2

        if l % 2:
            l += 1
            h_l += 1

        a_c *= 10**l
        sub_res *= 10**(h_l)
        return a_c + b_d + sub_res

if __name__ == "__main__":
    a, b = map(int, input().split())

    print(run_alg(a, b))  