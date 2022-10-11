d = {"Ivanov": 97832, "Petrov": 55521, "Kuznecov": 97832, "YA": 97832}
dict_new = dict()

for old_key, old_value in d.items():
    if old_value not in dict_new.keys():
        dict_new[old_value] = old_key
    else:
        if type(dict_new[old_value]) == str:
            dict_new[old_value] = [dict_new[old_value], old_key]
        else:
            dict_new[old_value] = [*dict_new[old_value], old_key]

print(dict_new)
