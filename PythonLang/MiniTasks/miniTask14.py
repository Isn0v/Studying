from functools import wraps

def coroutine(func):
    @wraps(func)
    def ret_func(*args, **kwargs):
        cr = func(*args, **kwargs)
        cr.send(None)
        return cr
    return ret_func

@coroutine
def storage():
    values = set()
    was_there = False

    while True:
        val = yield was_there
        was_there = val in values
        if not was_there:
            values.add(val)

st = storage()
print(st.send(42))
print(st.send(42))