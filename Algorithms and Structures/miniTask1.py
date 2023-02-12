def get_sub_del(n, d): # сложность (худший случай) - const*len(n) операций (len(n) - значность n-ого числа)
    n = str(n)
    for i in range(len(n)):
        sub_n = int(n[:i + 1])
        if sub_n > d:
            return sub_n
    return 0

# const операций
a, b = map(int, input().split())
res = ""
if a < b:
    raise Exception("Can't divide")

ost = a
#
while ost > b: #худший случай  - o(len(b)) (т. к. деление b раз, иначе меньше) 
    num = get_sub_del(ost, b) #o(len(a))
    ost = str(ost).replace(str(num), '')#const
    b_to_n = 0
    save_i = 0
    for i in range(1, 10): #const
        b_to_n += b
        if b_to_n + b > num:
            save_i = i
            break
    res += str(save_i)
    ost = int(str(num - b_to_n) + ost)

#const
res = res + f"*{b}"
if ost:
    res += " + " + str(ost)
print(res)

#вывод - сложность o(len(a) * len(b)) (худший случай)
#        в лучшем случае сложность может быть o(1) (пример: 0 / 14)