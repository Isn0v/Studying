import functools

def deprecated(func=None, since='', will_be_removed=''):

    if func is None:
        return functools.partial(deprecated, since=since, will_be_removed=will_be_removed)

    def decor(*args, **kwargs):

        st_default = f"Warning: function {func.__name__} is deprecated"

        if since:
            st_default += f" since version {since}"

        if will_be_removed:
            st_default += f". It will be removed in version {will_be_removed}."
        else:
            st_default += f". It will be removed in future versions."

        print(st_default)
        func(*args, **kwargs)

    return decor


@deprecated(since='1.1.0', will_be_removed='1.2.5')
def foo(a, b):
    print(f"Hi!!!, {a + b}")


foo(1, 2)
        