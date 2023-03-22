import random



def quick_sort(nums, start_ind, end_ind):
    if end_ind <= start_ind:
        return
    pivot_ind = random.randint(start_ind, end_ind)
    nums[pivot_ind], nums[start_ind] = nums[start_ind], nums[pivot_ind]
    i, j = start_ind + 1, start_ind + 1
    while j <= end_ind and i <= end_ind:
        if nums[j] <= nums[start_ind]:
            nums[i], nums[j] = nums[j], nums[i]
            i += 1
        j += 1
    nums[i - 1], nums[start_ind] = nums[start_ind], nums[i - 1]
    quick_sort(nums, start_ind, i - 2)
    quick_sort(nums, i, end_ind)
            
            

if __name__ == "__main__":
    nums = [5,2,3,1, 7, 8, 10, 5, 3]
    quick_sort(nums, 0, len(nums) - 1)
    print(nums)