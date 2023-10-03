class Task:
    def __init__(self, number, deadline, fine):
        self.number = number
        self.deadline = deadline
        self.fine = fine


class Node:
    def __init__(self, value):
        self.val = value
        self.ret_val = value
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

        if self.data[member_1].rank > self.data[member_2].rank:
            self.data[member_2].val = member_1
            self.data[member_1].ret_val = self.data[member_2].ret_val
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
        index = union_find.find(task.deadline - 1).ret_val
        union_find.union(index, index - 1)
        res[index] = task.number
        if index <= task.deadline - 1:
            res_val += task.fine
    return res, res_val


def check_naive(array):
    res = []
    res_val = 0
    for i in range(len(array)):
        task = array[i]
        res.append(task.number)
        if i <= task.deadline - 1:
            res_val += task.fine
    return res, res_val
