#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

int findSubArr(int* arr1, size_t size1, int* arr2, size_t size2){
    for(size_t i = 0; i < size1; i++){
        size_t jW = 0, iW = i;
        while (arr1[iW] == arr2[jW]){
            if(jW++ == size2 - 1){
                return i;
            }
            if(iW++ == size1 - 1){
                return -1;
            }
        }
    }

    return -1;
}


int main() {
    int arr1[] = {1,45,7,3,8,9};
    size_t size1 = 6;

    int arr2[] = {7,3,8},
    arr3[] = {8, 9, 9};
    size_t size2 = 3;

    printf("%d ", findSubArr(arr1, size1, arr3, size2));
}

