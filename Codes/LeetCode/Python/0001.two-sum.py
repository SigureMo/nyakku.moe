class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        d = {}
        for i, num in enumerate(nums):
            j = d.get(target-num)
            if j is not None:
                return [i, j]
            d[num] = i
