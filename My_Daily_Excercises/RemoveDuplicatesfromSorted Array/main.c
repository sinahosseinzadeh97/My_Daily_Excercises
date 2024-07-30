#include <stdio.h>

// Function to remove duplicates from the sorted array
int removeDuplicates(int* nums, int numsSize) {
    //If Array is Empty return 0
    if (numsSize==0) return 0;
    int j=1; //J is index for next unique element

    for (int i=1;i<numsSize;i++){
        if(nums[i]!=nums[i-1]){
            nums[j]=nums[i];
            j++;
        }
    }
    return j;

}

int main() {
    //Sample input Array
    int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    //Calculate the Size of Array
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k= removeDuplicates(nums,numsSize);
    printf("Number of unique Elemnts :%d\n",k);
    printf("Array after Removing Dupicates : ");
    for (int i=0;i<k;i++){
        printf("%d",nums[i]);
    }
    printf("\n");

    return 0;
}
