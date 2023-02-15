import alg
import os

def check(test_num: int):
    #p = os.getcwd()
    os.chdir(".\\Tests")
    try:
        with open(f".\\{test_num}.data", encoding="utf-8") as input:
            a, b = map(int, input.readline().split())
            assert a * b == alg.run_alg(a, b)

    finally:
        os.chdir("../..")


def test1():
    check(1)

def test2():
    check(2)
    
def test3():
    check(3)
    
def test4():
    check(4)
    
def test5():
    check(5)
