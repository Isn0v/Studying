num = int(input())
count = 0
if num < 0:
    count += 1
    while num != -1:
        if num & 1:
            count += 1
        num >>= 1

if num > 0:
    while num != 0:
        if num & 1:
            count += 1
        num >>= 1

print(count)