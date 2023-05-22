import bitsets
import math
import random

class Bitset:
    def __init__(self, value=0, length=0):
        self.value = value
        self.length = length or math.ceil(math.log2(value))

    def __str__(self):
        return bin(self.value)[2:]

    def __getitem__(self, ind):
        return (2 ** ind & self.value) >> ind

    def __setitem__(self, key, val):
        assert val == 0 or val == 1
        self.value = (self.value | (val << key))

    # def __iter__(self):
    #     for k in range(self.length):
    #         yield self[k]


def prime(n):
    for i in range(2, int(n**0.5) + 1):
        if (n%i==0):
            return False
    return True


def configure_bitset(requests, error_possibility):
    b = math.ceil(-math.log(2**math.log(2) * error_possibility) / math.log(2))
    

    n = int(b * requests)
    while not prime(n):
        n += 1

    k = int(math.log(2) * b)
    return n, k


def get_hash_func(m):
    a_arr = [random.randint(1, m - 1) for i in range(4)]

    def get_hashcode(x_arr):
        return (a_arr[0]*x_arr[0] + a_arr[1]*x_arr[1] + a_arr[2]*x_arr[2] + a_arr[3]*x_arr[3]) % m
    
    return get_hashcode
    
class Bloom_Filter:
    def __init__(self, m, funcs=list()):
        self.bitset = Bitset(length=m)
        self.funcs = funcs

    def append(self, val):
        for func in self.funcs:
            self.bitset[func(val)] = 1

    def lookup(self, val):
        for func in self.funcs:
            if self.bitset[func(val)] == 0:
                return False
        return True


 
if __name__ == "__main__":
    S = 100
    err = 0.3
    
    n, k = configure_bitset(S, err)
    
    hash_funcs = [get_hash_func(n) for i in range(k)]
    bloom_filter = Bloom_Filter(n, hash_funcs)
    
    ips = [[random.randint(0, 255) for i in range(4)] for j in range(100)]
    
    for ip in ips:
        bloom_filter.append(ip)
        
    print(bloom_filter.bitset)    
    
    
    new_ip = [random.randint(0, 255) for i in range(4)]
    while new_ip in ips:
        new_ip = [random.randint(0, 255) for i in range(4)]
    
    if bloom_filter.lookup(new_ip):
        print("Cringe happened")