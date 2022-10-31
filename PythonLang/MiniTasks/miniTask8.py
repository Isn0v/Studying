import functools

def deprecated(func=None, since=None, will_be_removed=None):

    if func is None:
        return functools.partial(deprecated, since=since, will_be_removed=will_be_removed)

    def decor(*args, **kwargs):
        if since and will_be_removed:
            print(f"Warning: function {func.__name__} is deprecated since version {since}. It will be removed in version {will_be_removed}")   
        elif will_be_removed: 
            print(f"Warning: function {func.__name__} is deprecated. It will be removed in version {will_be_removed}")
        elif since:
            print(f"Warning: function {func.__name__} is deprecated since version {since}. It will be removed in future versions")
        else:
            print(f"Warning: function {func.__name__} is deprecated. It will be removed in future versions.")
        return func()

    return decor


@deprecated
def foo():
    print("Hi!!!")


foo()
        