from typing import List

def countSmaller(self, nums: List[int]) -> List[int]:
        
    res  = [0] * len(nums)
    enum = list(enumerate(nums))
    
    self.merge_sort(enum, 0, len(nums) - 1, res)
    return res
    
def merge_sort(self, enum, start, end, res):
    if start >= end:
        return

    mid = start + (end - start) // 2
    self.merge_sort(enum, start, mid, res)
    self.merge_sort(enum, mid + 1, end, res)
    self.merge(enum, start, mid, end, res)

def merge(self, enum, start, mid, end, res):
    left_ptr, right_ptr = start, mid + 1
    inversion_count = 0
    temp = []
    
    while left_ptr <= mid and right_ptr <= end:
        if enum[left_ptr][1] <= enum[right_ptr][1]:
            temp.append(enum[left_ptr])
            res[enum[left_ptr][0]] += inversion_count
            left_ptr += 1
        else: # left number > right number (we need it)
            temp.append(enum[right_ptr])
            inversion_count += 1
            right_ptr += 1
    
    while left_ptr <= mid:
        temp.append(enum[left_ptr])
        res[enum[left_ptr][0]] += inversion_count
        left_ptr += 1
    
    while right_ptr <= end:         
        temp.append(enum[right_ptr])
        right_ptr += 1
    
    enum[start:end+1] = temp