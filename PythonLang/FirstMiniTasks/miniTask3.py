st = "1 2 | 3 4"
matr = []
for i in st.split("|"):
    matr.append(list(i.split(" ")))

for lst in matr:
    lst.remove('')
print(matr[0][1])
