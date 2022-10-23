num = int(input())
count = 0

if num == -1:
    print(2)
else:
    while 1:
        if num in [1, -1]:
            count += 1
            break
        if num & 1:
            count += 1
        num >>= 1
    print(count)
