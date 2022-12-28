def cycle(cls):
    while True:
        yield from cls

def take(it, stop_pos):
    lst = [] # не особо понял, какой здесь тип должен быть
    for i in range(stop_pos):
        lst.append(next(it))
    return lst

if __name__ == '__main__':
    print(take(cycle([1,2,3]), 10))

