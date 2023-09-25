# # class Node:
# #     def __init__(self, value, parent=None, left=None, right=None) -> None:
# #         if not parent:
# #             self.parent = self
# #         self.value = value
# #         self.left = left
# #         self.right = right

# #         if self.left is None and self.right is None:
# #             self.rank = 0
# #         elif self.left is None:
# #             self.rank = self.right.rank + 1
# #         elif self.right is None:
# #             self.rank = self.left.rank + 1
# #         else:
# #             self.rank = max(self.left.rank, self.right.rank) + 1

# # def find(node, started_node=None):
# #     if node.parent == node:
# #         started_node.parent = node
# #         return node
# #     find(node.parent, node)

# #value == ("A", 0, 0)
# def find(union_find: list, parents: list, value):
#     if union_find[value[1]] == parents[value[1]]:
#         return value
#     parents[value[1]] = find(union_find, parents, parents[value[1]])
#     return parents[value[1]]
    
# def union(union_find: list, parents: list, value1, value2):
#     a = find(union_find, parents, value1)
#     b = find(union_find, parents, value2)
#     if a[1] < b[1]:
#         parents[b[1]] = a
#     else:
#         parents[a[1]] = b
    

# # def union(node1, node2):
# #     a = find(node1)
# #     b = find(node2)
# #     if node1.rank > node2.rank:
# #         node2.parent = node1.parent
# #     else:
# #         node1.parent = node2.parent
# #         if node1.rank == node2.rank:
# #             node2.rank += 1




# if __name__ == "__main__":
#     DEFAULT = ("A", 0, 0)

#     # (("A", 0, 0), 0) -> ((task), index in working list): parent
#     tasks = [
#         ("A", 3, 25),
#         ("B", 4, 10),
#         ("C", 1, 30),
#         ("D", 3, 50),
#         ("E", 3, 20),
#     ]

#     #current task by index
#     union_find = [DEFAULT for i in range(len(tasks))]
#     #parent of current task by index
#     parents = [DEFAULT for i in range(len(tasks))]

#     visited = [0 for i in range(len(tasks))]

#     max_value = DEFAULT
#     max_i = 0
#     for i in range(len(tasks)):
#         if max_value[2] < tasks[i][2]:
#             max_value = tasks[i]
#             max_i = i

#     visited[max_i] = 1
#     union_find[max_value[1]] = max_value
#     parents[max_value[1]] = max_value

#     while not all(visited):
#         for i in range(len(tasks)):
#             if max_value[2] < tasks[i][2] and not visited[i]:
#                 max_value = tasks[i]
#                 max_i = i

#         visited[max_i] = 1
#         if union_find[max_value[1]] == DEFAULT:
#             union_find[max_value[1]] = max_value
#             parents[max_value[1]] = max_value
#         elif union_find[max_value[1]] != DEFAULT and find(union_find, parents, max_value) != union_find[0]:
#             union(union_find, parents, max_value, union_find[max_value[1]])
        
from typing import List


def find(v: int, parent: list):
    if v == parent[v]:
        return v
    else:
        parent[v] = find(parent[v], parent)
        return parent[v]


def union_sets(a: int, b: int, parent: list):
    a = find(a, parent)
    b = find(b, parent)
    if a < b:
        parent[b] = a
    if b < a:
        parent[a] = b


class Task:
    deadline = 0
    latency = 0

    def __init__(self, dead, penalty):
        self.deadline = dead
        self.latency = penalty

    def __eq__(self, other):
        return self.latency == other.penalty

    def __gt__(self, other):
        return self.latency > other.penalty

    def __lt__(self, other):
        return self.latency < other.penalty


def set_task(deadline, parents):
    parents[deadline] = deadline
    if deadline > 0 and parents[deadline - 1] != -1:
        union_sets(parents[deadline - 1], parents[deadline], parents)
    if deadline < len(parents) - 1 and parents[deadline + 1] != -1:
        union_sets(parents[deadline], parents[deadline + 1], parents)


def set_task_right(pos, parents):
    while parents[pos] != -1:
        pos = find(pos, parents) - 1
    set_task(pos, parents)


def good_solution(n, list_tasks: List[Task]):
    sum_latency = 0
    parent = [-1] * n
    list_tasks.sort(reverse=True)
    for i in range(n):
        deadline = list_tasks[i].deadline
        if parent[deadline] == -1:
            set_task(deadline, parent)
            continue
        new_place = find(deadline, parent) - 1
        if new_place >= 0:
            set_task(new_place, parent)
            continue
        sum_latency += list_tasks[i].latency
        set_task_right(len(parent) - 1, parent)
    return sum_latency


def simple_solution(n, list_tasks: List[Task]):
    list_tasks.sort(reverse=True)
    sum_latency = 0
    for i in range(n):
        if i < list_tasks[i].deadline:
            sum_latency += list_tasks[i].latency
    return sum_latency


tasks = [Task(3, 25), Task(3, 10),Task(0, 30), Task(2, 50), Task(2, 20)]
print(good_solution(5,tasks),simple_solution(5,tasks))

tasks = [Task(3, 100), Task(3, 80), Task(1, 90), Task(0, 95), Task( 2, 40)]
print(good_solution(5,tasks),simple_solution(5,tasks))

tasks = [Task(1, 60), Task(1, 40), Task(1, 70), Task( 0, 30), Task(3, 55)]
print(good_solution(5,tasks), simple_solution(5,tasks))
