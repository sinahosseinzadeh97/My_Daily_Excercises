#include <stdio.h>
#define DIM 10
int main(){
    int array[DIM]; //Array to store DIM integer values
    int result[DIM];//Array to store the non-zero values after shifting
    int i,j=0;//'i' is looping,'j' keeps track of the result array
    //Step1:Read the array from the user input;
    printf("Enter %d integer values :\n",DIM);
    for(i=0;i<DIM;i++){
        scanf("%d",&array[i]);
    }
    //Step2:Eliminate zeros shift the values array
    for (i=0;i<DIM;i++){
        if (array[i]!=0){
            result[j]=array[i];//Copy non-zero elements
            j++;//Move to the nex postion in the result array
        }
    }
    //step3:Print the resulting array meanifull elemts only
    printf("Array after eliminating zeros :\n");
    for (i=0;i<j;i++){
        printf("%d",result[i]);
    }
    printf("\n");
    return 0;
}
