def mult(x, y, z):
    return x + y + z

def specialize(function, *args, **kwargs):
    args_count = len(args) + len(kwargs)
    if args_count == function.__code__.co_argcount:
        def new_function():
            return function(*args, **kwargs)
    else:
        def new_function(*new_args, **new_kwargs):
            for arg, value in new_kwargs.items():
                if arg not in function.__code__.co_varnames:
                    raise Exception(f"{arg}: Function doesn't have such argument(s) name(s)")
            return function(*new_args, *args, **new_kwargs, **kwargs)
    for arg, value in kwargs.items():
        if arg not in function.__code__.co_varnames:
            raise Exception(f"{arg}: Function doesn't have such argument(s) name(s)")
    return new_function

#Use variable name starting from right(all args count must be equal to function arg count)
#or it raises an Exception
plus_one = specialize(mult, z=1)
print(plus_one(1, 2)) # >> 4
