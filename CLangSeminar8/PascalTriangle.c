#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

//I don't know how to explain, but this code
//works only in debug mode
//We need to discuss it on the next lecture or lesson

int factorial(int num){
    int res = 1;
    for(int i = 1; i <= num; i++){
        res *= i;
    }
    return res;
}

int binomCoef(int k, int n){
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int** createPascalTriangle(int N){
    int** matrix = malloc( N * (sizeof(int)) );
    if(!matrix){
        return NULL;
    }
    for(int i = 0; i < N; i++){
        matrix[i] = malloc((i + 1) * sizeof(int));
        if(!matrix[i]){
            return NULL;
        }
    }
    return matrix;
}

int fillWithBinomCoef(int** matrix, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i + 1; j++){
            matrix[i][j] = binomCoef(j, i);
        }
    }
    return 1;
}

void display(int** matrix, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i + 1; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N = 6;
    int** matrix = createPascalTriangle(N);
    if(!matrix){
        printf("Allocation error");
        exit(1);
    }
    fillWithBinomCoef(matrix, N);
    display(matrix, N);

    for(int i = 0; i < N; i++){
        free(matrix[i]);
    }
    free(matrix);
}

