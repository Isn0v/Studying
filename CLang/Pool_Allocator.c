#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MAX_SIZE 100 * 1024 * 1024
#define CHUNK_SIZE 1024

typedef char byte;

typedef struct{
    void* head;
    void* cur;
} allocator;

void init_alloc(allocator* alloc){
    alloc->head = malloc(sizeof(byte) * MAX_SIZE);
    if (alloc->head == NULL){
        printf("NULL Error in allocator memory allocation");
        exit(0);
    }
    alloc->cur = alloc->head;

    size_t CHUNKS_COUNT = MAX_SIZE / CHUNK_SIZE;
    for(size_t it = 0; it < CHUNKS_COUNT - 1; it++){
        *(void**)((byte*)alloc->head + CHUNK_SIZE * it) = (byte*)(alloc->head + CHUNK_SIZE * (it + 1));
    }
    *(void**)((byte*)alloc->head + CHUNK_SIZE * (CHUNKS_COUNT - 1)) = NULL;
}

void* my_alloc(allocator* alloc){
    void* ret_ptr = alloc->cur;
    alloc->cur = *((void**)ret_ptr);
    return  ret_ptr;
}

void my_free(allocator* allocator, void* ptr){
    void* tmp = allocator->cur;
    allocator->cur = ptr;
    *((void**)allocator->cur) = tmp;
}


void free_allocator(allocator* alloc){
    free(alloc->head);
    free(alloc);
}