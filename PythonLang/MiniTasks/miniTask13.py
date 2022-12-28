def chain(*iters):
    for it in iters:
        yield from it

if __name__ == '__main__':
    lst = [342, 456, 7]
    print(list(chain([12, 5, 8], (7, 'sdj', 'hi'), lst)))