def flatten(lst: list, depth=-1) -> list:
    
    res_lst = []
    for i in range(len(lst)):
        if not isinstance(lst[i], list) or depth == 0:
            res_lst.append(lst[i])
        else:
            if depth == -1:
                res_lst = [*res_lst, *flatten(lst[i])]
            elif depth > 0:
                res_lst = [*res_lst, *flatten(lst[i], depth - 1)]

    return res_lst


lst = [1, 2, [4, 5], [6, [7]], 8]
print(flatten(lst))
