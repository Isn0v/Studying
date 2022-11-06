def format_table(benchmarks: list, algos: list, results: list):
    max_width = 0
    tmp = [i for i in benchmarks]
    tmp.extend(algos)
    for i in results:
        tmp.extend(i)
    tmp.append("Benchmark")

    for st in tmp:
        max_width = max(max_width, len(str(st)))

    res_str = f"| Benchmark " + " "*(max_width - 9)

    for word in algos:
        res_str += f"| {word} " + " "*(max_width - len(word))

    res_str += "|\n"
    base_len = len(res_str) - 3
    res_str += "|" + "-"*base_len + "|\n"

    for lst in zip(benchmarks, results):
        res_str += f"| {lst[0]} " + " "*(max_width - len(str(lst[0])))
        for num in lst[1]:
            res_str += f"| {num} " + " "*(max_width - len(str(num)))
        res_str += "|\n"

    print(res_str)

format_table(["best case", "worst case"], 
["quick sort", "merge sort", "bubble sort"], 
[[1.23, 1.56, 2.0], [3.3, 2.9, 3.9]])




