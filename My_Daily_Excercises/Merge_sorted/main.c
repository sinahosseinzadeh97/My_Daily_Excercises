#include <stdio.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = m - 1;  // Pointer for the last element in the initial part of nums1
    int j = n - 1;  // Pointer for the last element in nums2
    int k = m + n - 1;  // Pointer for the last position in nums1

    // Merge nums1 and nums2 starting from the end
    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
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
    int nums1[6] = {4, 5, 6, 0, 0, 0};
    int nums2[3] = {1, 2, 3};
    int m = 3;
    int n = 3;

    merge(nums1, 6, m, nums2, 3, n);
    printArray(nums1, 6);  // Expected output: 1 2 3 4 5 6

    return 0;
}
