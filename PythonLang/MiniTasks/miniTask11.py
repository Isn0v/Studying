class Singleton:
    instance = None

    def __new__(cls, *args, **kwargs):
        if not Singleton.instance:
            Singleton.instance = super(Singleton, cls).__new__(cls)
        else:
            cls.__init__ = lambda *args, **kwargs: None
        return Singleton.instance


class Counter:
    def __init__(self, count) -> None:
        self.count = count

    def increment(self):
        self.count += 1


class GlobalCounter(Singleton, Counter):
    def __init__(self, count=0) -> None:
        self.count = count
        Singleton.__init__(Counter)
        print("init")
            


if __name__ == '__main__':
    gc1 = GlobalCounter()
    #gc2 = GlobalCounter()
    gc2 = GlobalCounter(5)
    print(gc2.count)
    print(id(gc1) == id(gc2))