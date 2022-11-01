d = {(1, 2): 97832, "Petrov": 55521, "Kuznecov": 97832, "YA": 97832}
dict_new = dict()
new_key_value = []
try:
    for old_key, old_value in d.items():
        for i in range(len(new_key_value)):
            if new_key_value[i][0] == old_value:
                new_key_value[i].append(old_key)
                break
        else:
            new_key_value.append([old_value, old_key])
    for lst in new_key_value:
        dict_new[lst[0]] = tuple(lst[1:])

except Exception:
    print("Error")

print(dict_new)
