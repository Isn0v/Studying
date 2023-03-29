import random

def quick_sort(nums, start_ind, end_ind):
    if end_ind <= start_ind:
        return
    pivot_ind = random.randint(start_ind, end_ind)
    nums[pivot_ind], nums[start_ind] = nums[start_ind], nums[pivot_ind]
    
    is_all_eq = True
    
    i, j = start_ind + 1, start_ind + 1     
    while j <= end_ind and i <= end_ind:
        if nums[start_ind] != nums[j]:
            is_all_eq = False
        
        if nums[j] < nums[start_ind]:
            nums[i], nums[j] = nums[j], nums[i]
            i += 1
        j += 1
        
    if is_all_eq:
        return
        
    nums[i - 1], nums[start_ind] = nums[start_ind], nums[i - 1]
    quick_sort(nums, start_ind, i - 2)
    quick_sort(nums, i, end_ind)
            
            

if __name__ == "__main__":
    nums = []
    nums.append(3)
    for i in range(49999):
        nums.append(2)
    quick_sort(nums, 0, len(nums) - 1)
    print(nums)