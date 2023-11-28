import random

class Node:
    def __init__(self, value):
        self.value = value
        self.priority = random.random()
        self.size = 1
        self.left = None
        self.right = None

class ImplicitTreap:
    def __init__(self):
        self.root = None

    def _size(self, node):
        return node.size if node else 0

    def _update_size(self, node):
        if node:
            node.size = self._size(node.left) + self._size(node.right) + 1

    def _merge(self, left, right):
        if not left or not right:
            return left if not right else right

        if left.priority > right.priority:
            left.right = self._merge(left.right, right)
            self._update_size(left)
            return left
        else:
            right.left = self._merge(left, right.left)
            self._update_size(right)
            return right

    def _split(self, node, index):
        if not node:
            return None, None

        if index <= self._size(node.left):
            left, right = self._split(node.left, index)
            node.left = right
            self._update_size(node)
            return left, node
        else:
            left, right = self._split(node.right, index - self._size(node.left) - 1)
            node.right = left
            self._update_size(node)
            return node, right

    def _insert_at_index(self, index, value):
        left, right = self._split(self.root, index)
        new_node = Node(value)
        self.root = self._merge(self._merge(left, new_node), right)

    def build(self, array):
        for i in range(len(array)):
            self._insert_at_index(i, array[i])

    def sum(self, from_idx, to_idx):
        left, mid = self._split(self.root, from_idx)
        mid, right = self._split(mid, to_idx - from_idx + 1)
        total_sum = self._get_sum(mid)
        self.root = self._merge(left, self._merge(mid, right))
        return total_sum

    def _get_sum(self, node):
        return node.value if node else 0

# Пример использования:

# Создание неявного декартового дерева и его построение из массива
array = [1, 3, 5, 7, 9, 11]
treap = ImplicitTreap()
treap.build(array)

# Получение суммы элементов от индекса 1 до индекса 4 включительно
result_sum = treap.sum(1, 4)
print(result_sum)
