def color_sort(nums):
    i = 0
    counter_2 = 0
    while i < len(nums) - counter_2:
        if nums[i] == 0:
            nums.insert(0, nums.pop(i))
            
        elif nums[i] == 2:
            nums.append(nums.pop(i))
            i -= 1
            counter_2 += 1
        i += 1
            
if __name__ == "__main__":
    nums = [2,0,2,1,1,0]
    color_sort(nums)
    print(nums)