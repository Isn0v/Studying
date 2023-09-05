def canJump(self, nums) -> bool:
    prev = nums[0]
    pos = 1
    if len(nums) == 1:
        return True
    if len(nums) == 0 or prev == 0:
        return False
    while pos < len(nums) - 1:
        prev = max(prev - 1, nums[pos])
        if not prev:
            return False
        pos += 1
    return True