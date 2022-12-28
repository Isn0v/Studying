DEBUG = 1

class LRUCache:
    def __init__(self, capacity=3) -> None:
        self._capacity = capacity
        self.data = dict()
        self.key_priorities = list([None, 0] for i in range(capacity)) #[[key, priority]]

    def get_key_index(self, key):
        for i in range(len(self.key_priorities)):
            if self.key_priorities[i][0] == key:
                return i
        return -1

    def update(self, key):
        index = self.get_key_index(key)
        self.key_priorities[index][1] += 1
        if index == 0:
            return
        while (index != 0 and self.key_priorities[index][1] > self.key_priorities[index - 1][1]):
            self.key_priorities[index], self.key_priorities[index - 1] = self.key_priorities[index - 1], self.key_priorities[index]
            index -= 1

    def print_debug(self):
        print(self.data)
        print(self.key_priorities, end="\n\n")

    def get(self, key):
        self.update(key)
        if DEBUG:
            self.print_debug()
        return self.data[key]

    def put(self, key, value):
        i = 1
        while i != self._capacity:
            if self.key_priorities[-i - 1][0] is None:
                self.key_priorities[-i - 1][0], self.key_priorities[-i - 1][1] = key, 0
                self.data[key] = value
                break
            i += 1
        else:
            if self.key_priorities[-1][0] is not None:
                del self.data[self.key_priorities[-1][0]]
            self.key_priorities[-i][0], self.key_priorities[-i][1] = key, 0
            self.data[key] = value
        if DEBUG:
            self.print_debug()


if __name__ == "__main__":
    lru = LRUCache(3)
    for i in range(3):
        lru.put(f"key{i + 1}", f"value{i + 1}")

    for i in range(3):
        lru.get("key1")

    # for i in range(3):
    #     lru.get("key4")

    # for i in range(4):
    #     lru.get("key5")

    # for i in range(2):
    #     lru.get("key3")

    # lru.put("new_key", "new_val")

    # for i in range(10):
    #     lru.get("new_key")

    # for i in range(56):
    #     lru.get("key1")

    # lru.put("new_key", "new_val")
