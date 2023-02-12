import alg
import os

def check(test_num: int):
    p = os.getcwd()
    os.chdir(".\\miniTask2\\Tests")
    try:
        with open(f".\\{test_num}.data", encoding="utf-8") as input, \
            open(f".\\{test_num}.expected", encoding="utf-8") as output:
                a, b = input.readline().split()
                assert int(output.readline()) == alg.run_alg(a, b)

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

def test6():
    check(6)