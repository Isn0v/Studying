#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


#define MAX_SIZE 100*1024*1024
#define BLOCK_SIZE 1024
#define ARR_OF_CAPS {64, 256, 512, 1024}
#define LEN_CAPS 4


int CAPS[LEN_CAPS] = {64, 256, 512, 1024};


typedef struct {
    void* head;
    int size;
    void* static_head;
} block;


block* BLOCKS;


int _what_block(void* ptr){
    size_t iter = 0;

    for ( ;iter < LEN_CAPS - 1; iter++){
        if (BLOCKS[iter].static_head<= ptr && BLOCKS[iter + 1].static_head > ptr){
            return iter;
        }
    }

    if (BLOCKS[iter].static_head >= ptr){
        return iter;
    } else {
        assert(0);
    }
}


void _write_address(void* head, size_t size, size_t len){
    size_t count_blocks = len / size;
    size_t iter = 0;

    for ( ; iter < count_blocks - 1; iter++){
        *((void**)((char*) head + size * iter)) = ((char*) head + size * (iter + 1));
    }

    *((void**)((char*) head + size * (iter))) = 0;
}


void init_mylloc(){
    size_t len_arrays = 0;
    size_t iter = 1;

    len_arrays = MAX_SIZE / LEN_CAPS;

    BLOCKS = (block*) malloc(sizeof(block) * 4);

    BLOCKS[0].head = malloc(MAX_SIZE);
    BLOCKS[0].size = CAPS[0];
    BLOCKS[0].static_head = BLOCKS[0].head;
    _write_address(BLOCKS[0].head, BLOCKS[0].size, len_arrays);

    for ( ; iter < LEN_CAPS; iter++){
        BLOCKS[iter].head = (void *) ((char *) BLOCKS[iter - 1].head + len_arrays);
        BLOCKS[iter].static_head = BLOCKS[iter].head;
        BLOCKS[iter].size = CAPS[iter];
        _write_address(BLOCKS[iter].head, BLOCKS[iter].size, len_arrays);
    }
}


void* _return_address(void** HEAD){
    void* return_ptr = *HEAD;

    *HEAD = *((void **) *HEAD);

    if (!*HEAD){
        exit(0);
    }

    return return_ptr;
}


void* mylloc(size_t size){
    size_t iter = 0;

    for ( ;iter < LEN_CAPS; iter++){
        if (size < BLOCKS[iter].size){
            return _return_address(&BLOCKS[iter].head);
        }
    }

    return 0;
}


void _free_address(void* ptr, void** HEAD){
    *((void **) ptr) = (void *) *HEAD;
    *HEAD = ptr;
}


void myee(void* ptr){
    _free_address(ptr, &BLOCKS[_what_block(ptr)].head);
}


void* myclloc(size_t num, size_t size){
    void* return_ptr = mylloc(num * size);
    if (!return_ptr){
        return 0;
    }

    size_t iter = 0;
    for ( ; iter < num * size; iter++){
        *((char*) return_ptr + iter) = 0;
    }

    return return_ptr;
}


void* myealloc(void* ptr, size_t size){
    int previous_block = _what_block(ptr);

    if (BLOCKS[previous_block].size >= size){
        return ptr;
    } else {
        void* return_ptr = mylloc(size);
        size_t iter = 0;

        for ( ; iter < BLOCKS[previous_block].size; iter++){
            *((char*) return_ptr + iter) = *((char *) ptr + iter);
        }

        _free_address(ptr, &BLOCKS[previous_block].head);

        return return_ptr;
    }
}


void free_mylloc(){
    free(BLOCKS[0].static_head);
}
