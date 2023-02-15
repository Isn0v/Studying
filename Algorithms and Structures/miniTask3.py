def search(nums, target):
    left = 0
    right = len(nums)
    res_ind = -1
    it_ind = right // 2
    while True:
        if left >= right - 1 and nums[it_ind] != target:
            break
        if nums[it_ind] == target:
            res_ind = it_ind
            break
        elif target < nums[it_ind]:
            right = it_ind
        elif target > nums[it_ind]:
            left = it_ind
        it_ind = (left + right) // 2
    return res_ind


lst = [1,42,8,9,14,188,19,65]
print(search(lst))