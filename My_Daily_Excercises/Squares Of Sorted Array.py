from typing import List


class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        # Initialize two pointers
        left, right = 0, len(nums) - 1
        result = [0] * len(nums)  # Create a result array to store the sorted squares
        pos = len(nums) - 1  # Start filling the result array from the end

        # Loop until the pointers cross
        while left <= right:
            left_square = nums[left] ** 2  # Square of the left pointer
            right_square = nums[right] ** 2  # Square of the right pointer

            # Compare squares and place the larger one in the result array
            if left_square > right_square:
                result[pos] = left_square
                left += 1  # Move left pointer inward
            else:
                result[pos] = right_square
                right -= 1  # Move right pointer inward

            # Move the position in the result array backward
            pos -= 1

        return result
