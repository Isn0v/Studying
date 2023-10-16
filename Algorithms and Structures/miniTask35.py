class Task:
    def __init__(self, number, deadline, fine):
        self.number = number
        self.deadline = deadline
        self.fine = fine


class Node:
    def __init__(self, value):
        self.val = value
        self.left_border = value
        self.rank = 0


class UnionFind:
    def __init__(self, amount):
        self.data = [Node(i) for i in range(amount)]

    def find(self, val):
        if val == -1:
            val = len(self.data) - 1

        next_val = self.data[val].val
        if next_val == val:
            return self.data[val]
        else:
            member = self.find(next_val)
            self.data[val].val = member.val
            return member

    def union(self, index_1, index_2):
        member_1, member_2 = self.find(index_1).val, self.find(index_2).val
        if member_1 == member_2:
            return

        self.data[member_1].left_border = self.data[member_2].left_border = min(self.data[member_1].left_border, self.data[member_2].left_border)
        
        if self.data[member_1].rank > self.data[member_2].rank:
            self.data[member_2].val = member_1
        else: #member_2.rank <= member_1.rank
            self.data[member_1].val = member_2
            if self.data[member_1].rank == self.data[member_2].rank:
                self.data[member_2].rank += 1

#assuming array is sorted properly
def check_smart(arr):
    union_find = UnionFind(len(arr))
    res = [0] * len(arr)
    res_val = 0

    for task in arr:
        index = union_find.find(task.deadline - 1).left_border
        union_find.union(index, index - 1)
        res[index] = task.number
        if index <= task.deadline - 1:
            res_val += task.fine
    return res, res_val


def check_naive(arr):
    res = []
    res_val = 0
    for i in range(len(arr)):
        task = arr[i]
        res.append(task.number)
        if i <= task.deadline - 1:
            res_val += task.fine
    return res, res_val


if __name__ == "__main__":
    tasks = [Task("A", 1, 20), Task("B", 1, 20), Task("C", 1, 20), Task("D", 1, 20), Task("E", 1, 20), Task("F", 1, 20)]
    tasks.sort(key=lambda x: x.fine, reverse=True)
    res_smart = check_smart(tasks)
    res_naive = check_naive(tasks)
    print(res_smart, res_naive)
    
    tasks = [Task("A", 4, 80), Task("B", 4, 100), Task("C", 2, 90), Task("D", 1, 95), Task("E", 3, 40)]
    tasks.sort(key=lambda x: x.fine, reverse=True)
    res_smart = check_smart(tasks)
    res_naive = check_naive(tasks)
    print(res_smart, res_naive)

    tasks = [Task("A", 5, 60), Task("B", 1, 10), Task("C", 1, 10), Task("D", 1, 10), Task("E", 1, 10), Task("F", 1, 10)]
    tasks.sort(key=lambda x: x.fine, reverse=True)
    res_smart = check_smart(tasks)
    res_naive = check_naive(tasks)
    print(res_smart, res_naive)

    tasks = [Task("A", 3, 25), Task("B", 4, 10), Task("C", 1, 30), Task("D", 3, 50), Task("E", 3, 20)]
    tasks.sort(key=lambda x: x.fine, reverse=True)
    res_smart = check_smart(tasks)
    res_naive = check_naive(tasks)
    print(res_smart, res_naive)