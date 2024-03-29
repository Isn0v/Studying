import math

def shell_sort(lst: list):
    st = int(math.log(len(lst), 2))
    step = 2**st - 1
    while step > 0:
        for i in range(step, len(lst)):
            j = i
            start_subseq = j - step
            while start_subseq >= 0 and lst[start_subseq] > lst[j]:
                lst[start_subseq], lst[j] = lst[j], lst[start_subseq]
                j = start_subseq
                start_subseq = j - step
        st -= 1
        step = 2**st - 1
    return lst

def h_index(lst):
    lst = shell_sort(lst)[::-1]

    for i in range(len(lst)):
        if lst[i] <= i:
            return i

    return len(lst)

            

if __name__ == "__main__":
    lst = [1, 2, 24, 546, 234, 6, 4]
    print(shell_sort(lst))