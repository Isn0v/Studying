from random import randint

def partition(nums, ind):
    pivot = nums[ind]
    nums[ind], nums[0] = nums[0], nums[ind]
    
    l, h, c = 0, 0, 1     
    while c < len(nums):
        if nums[c] < nums[h]:
            tmp = nums[c]
            nums[c] = nums[h + 1]
            nums[h + 1] = nums[l]
            nums[l] = tmp
            l += 1
            h += 1
            c += 1
            
        elif nums[c] == pivot: 
            nums[h + 1], nums[c] = nums[c], nums[h + 1]
            h += 1
            c += 1
            
        else:
            c += 1
    return h
        
    
def kth(nums, k):
    if len(nums) == 1:
        return nums[0]
    
    pivot = randint(0, len(nums) - 1)
    p = partition(nums, pivot)
    
    if p == k:
        return nums[p]
    elif p > k:
        return kth(nums[:p], k)
    else:
        return kth(nums[p + 1:], k - p - 1)
    
if __name__ == "__main__":
    nums = [3,2,3,1,2,4,5,5,6]
    print(nums)
    
    print(kth(nums, len(nums) - 4))
    nums.sort()
    print(nums)
    