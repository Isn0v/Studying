class Singleton:
    __created = None

    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance


class Counter:
    def __init__(self, count) -> None:
        self.count = count

    def increment(self):
        self.count += 1


class GlobalCounter(Singleton, Counter):
    def __init__(self, count=0) -> None:
        Singleton.__init__(self)
        Counter.__init__(self, count)


if __name__ == '__main__':
    gc1 = GlobalCounter()
    gc2 = GlobalCounter()
    #gc2 = GlobalCounter(5) - ошибку выдает, надо обсудить
    print(id(gc1) == id(gc2))