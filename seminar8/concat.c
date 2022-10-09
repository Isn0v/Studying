#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

int concatArrs(int* resArr, int* arr1, size_t size1, int* arr2, size_t size2){
    if(!resArr){
        return 0;
    }
    
    for(size_t i = 0; i < size1; i++){
        resArr[i] = arr1[i];
    }

    for(size_t i = size1; i < (size2 + size1); i++){
        resArr[i] = arr2[i - size1];
    }
    return 1;
}


int main() {
    int arr1[] = {1,45,7,3,8,9};
    size_t size1 = 6;

    int arr2[] = {4,7,1,8,34,87,5};
    size_t size2 = 7;

    int* resArr = (int*) malloc((size1 + size2) * sizeof(int));
    if(!resArr){
        printf("Allocation error");
    }

    if(!concatArrs(resArr, arr1, 6, arr2, 7)){
        exit(1); //error
    }

    for(size_t i = 0; i < (size1 + size2); i++){
        printf("%d ", resArr[i]);
    }

    free(resArr);
}

