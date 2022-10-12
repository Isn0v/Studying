st = "1.0 2.0 | 3.0 4.0"
matr = []
for i in st.split(" | "):
    matr.append(list(map(float, list(i.split(" ")))))

print(matr) #matr[row][col]
