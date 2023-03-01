from miniTask5 import shell_sort

def wiggleSort(nums: list[int]):
    nums = shell_sort(nums)
    nums1 = nums[:len(nums) // 2 + len(nums) % 2]
    nums2 = nums[len(nums) // 2 + len(nums) % 2:][::-1]
    
    for i in range(len(nums)):
        if i % 2:
            nums[i] = nums2[i // 2]
        else:
            nums[i] = nums1[i // 2 + i % 2]


if __name__ == "__main__":
    lst = [1,5,1,1,6,4]
    wiggleSort(lst)
    print(lst)

