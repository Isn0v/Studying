def flatten(lst: list) -> list:
    res_lst = []
    for i in range(len(lst)):
        if not isinstance(lst[i], list):
            res_lst.append(lst[i])
        else:
            res_lst = [*res_lst, *flatten(lst[i])]
    return res_lst


lst = [1, 2, [4, 5], [6, [7]], 8]
print(flatten(lst))
