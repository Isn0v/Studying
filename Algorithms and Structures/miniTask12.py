import random

def quick_sort(nums, start_ind, end_ind):
    if end_ind <= start_ind:
        return
    
    pivot_ind = random.randint(start_ind, end_ind)
    nums[pivot_ind], nums[end_ind] = nums[start_ind], nums[end_ind]
    
    
    left, cur, right = start_ind, start_ind, start_ind
    
    while cur < end_ind:
        
        if nums[cur] < nums[pivot_ind]:
            tmp = nums[cur]
            nums[cur] = nums[right]
            nums[right] = nums[left]
            nums[left] = tmp
            left += 1
            right += 1
            
        elif nums[cur] == nums[pivot_ind]:
            nums[cur], nums[right] = nums[right], nums[cur]
            right += 1
        
        cur += 1
        
    nums[right], nums[end_ind] = nums[end_ind], nums[right]
        
    quick_sort(nums, start_ind, left - 1)
    quick_sort(nums, right + 1, end_ind)
            
            

if __name__ == "__main__":
    nums = [5, 2, 3, 1]
    # nums.append(3)
    # for i in range(49999):
    #     nums.append(2)
    quick_sort(nums, 0, len(nums) - 1)
    print(nums)