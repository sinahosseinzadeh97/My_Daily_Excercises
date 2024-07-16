#include <stdio.h>

// Function to remove all occurrences of val in nums in-place
int removeElement(int* nums, int numsSize, int val) {
    int k = 0;  // Pointer for the next position to place non-val elements

    // Traverse through all elements in nums
    for (int i = 0; i < numsSize; i++) {
        // If the current element is not equal to val
        if (nums[i] != val) {
            // Place it at the position pointed by k
            nums[k] = nums[i];
            // Move k to the next position
            k++;
        }
    }

    // k is the count of elements that are not equal to val
    return k;
}

// Helper function to print the array (for testing)
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function (for testing)
int main() {
    int nums1[] = {3, 2, 2, 3};
    int val1 = 3;
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int k1 = removeElement(nums1, size1, val1);
    printf("k = %d, nums = ", k1);
    printArray(nums1, k1);  // Expected output: k = 2, nums = [2, 2]

    int nums2[] = {0, 1, 2, 2, 3, 0, 4, 2};
    int val2 = 2;
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int k2 = removeElement(nums2, size2, val2);
    printf("k = %d, nums = ", k2);
    printArray(nums2, k2);  // Expected output: k = 5, nums = [0, 1, 3, 0, 4]

    return 0;
}
