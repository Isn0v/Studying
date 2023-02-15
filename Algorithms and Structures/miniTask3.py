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


lst = [1,4,82,94353,1433,18,1239,6]
print(search(lst))