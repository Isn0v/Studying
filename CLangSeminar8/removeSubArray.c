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

int removeSubArr(int* arr, size_t* sizeArr, int* subArr, size_t subSize){
    size_t size = *sizeArr;
    int rmFromIndex = findSubArr(arr, size, subArr, subSize);
    if(rmFromIndex == -1){
        return 1; //nothing more to delete
    }

    int* tmp = malloc(size * (sizeof(int)));
    if(!tmp){
        return 0; // allocation error
    }

    for(size_t  i = 0; i < size; i++){
        tmp[i] = arr[i];
    }

    arr = realloc(arr, (size - subSize) * sizeof(int));
    if(!arr){
        return 0;
    }

    size_t i = 0, iForArr = 0;
    while(iForArr < (size - subSize)){
        arr[iForArr++] = tmp[i];
        if(i++ == rmFromIndex - 1){
            i += subSize;
        }
    }

    free(tmp);
    *sizeArr = (size - subSize);
    removeSubArr(arr, sizeArr, subArr, subSize);
}

int main() {
    int* arr1;
    size_t size1 = 10;
    arr1 = malloc(size1 * sizeof(int));
    if(!arr1){
        printf("Allocation error\n");
        exit(1);
    }

    for(size_t i = 0; i < size1; i++){
        scanf("%d", &arr1[i]);
    }

    int arr3[] = {8, 9, 9};
    size_t size2 = 3;

    int res = removeSubArr(arr1, &size1, arr3, size2);
    if(!res){
        printf("Allocation error\n");
        exit(1);
    }
    if(res){
        printf("Removed somehow\n");
    }

    for(size_t  i = 0; i < size1; i++){
        printf("%d ", arr1[i]);
    }
    free(arr1);
}

