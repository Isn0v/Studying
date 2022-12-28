#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

int* resize(int* list, size_t size, int* capacity){
    int* tmp = list;

    list = malloc((int)pow(2, *capacity) * sizeof(int));
    if(!list){
        return NULL;
    }

    for(int i = 0; i < size; i++){
        list[i] = tmp[i];
    }
    free(tmp);
    return list;
}

int main() {
    int  scanNum = -1;
    size_t capacity = 1;
    size_t size = 0;
    int* list = malloc(2 * sizeof(int));
    if(!list){
        printf("Allocation error");
        exit(1);
    }

    while (scanNum != 0){
        scanf("%d", &scanNum);

        if(size == (int)pow(2, capacity)){
            capacity++;
            list = resize(list, size, &capacity);
            if(!list){
                printf("Allocation error");
                exit(1);
            }
        }

        list[size++] = scanNum;
        for(int i = 0; i < size;  i++){
            printf("%d ", list[i]);
        }
        printf("\n");
    }
    free(list);
}
