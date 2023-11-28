class Node(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.total = 0
        self.left = None
        self.right = None


class NumArray(object):

    def __init__(self, nums):
        def create_tree(nums, start, end):
            if start > end:
                return None
            if start == end:
                node = Node(start, end)
                node.total = nums[start]
                return node
            mid = (start + end) // 2
            root = Node(start, end)
            root.left = create_tree(nums, start, mid)
            root.right = create_tree(nums, mid + 1, end)
            root.total = root.left.total + root.right.total
            return root

        self.root = create_tree(nums, 0, len(nums) - 1)

    def update(self, i, val):
        def update_value(node, index, value):
            if node.start == node.end:
                node.total = value
                return value
            mid = (node.start + node.end) // 2
            if index <= mid:
                update_value(node.left, index, value)
            else:
                update_value(node.right, index, value)
            node.total = node.left.total + node.right.total
            return node.total

        return update_value(self.root, i, val)

    def sumRange(self, i, j):
        def range_sum(root, start, end):
            if root.start == start and root.end == end:
                return root.total
            
            mid = (root.start + root.end) // 2
            
            if end <= mid:
                return range_sum(root.left, start, end)
            elif start >= mid + 1:
                return range_sum(root.right, start, end)
            else:
                return range_sum(root.left, start, mid) + range_sum(root.right, mid + 1, end)
            
        return range_sum(self.root, i, j)
