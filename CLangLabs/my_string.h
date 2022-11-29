#ifndef MY_STRING_LIB_H
#define MY_STRING_LIB_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct String{
    size_t size;
    size_t capacity;
    char* string_array;
} string;

void null_check(void* ptr){
    if (ptr == NULL){
        printf("Error: nullable pointer at %d line in file %s", __LINE__, __FILE__);
    }
}

void string_resize(string* str){
    str->capacity *= 2;
    str->string_array = (char*)realloc(str->string_array, str->capacity);
    null_check(str->string_array);
}

size_t define_capacity(size_t n){
    size_t iter = 1;
    while (iter < n) {
        iter <<= 1;
    }
    return iter;
}

//initialization
string* string_init(char* char_arr){
    size_t len = strlen(char_arr);

    string* ret_str = (string*)malloc(sizeof(string));
    null_check(ret_str);

    size_t cap = define_capacity(len);
    char* tmp = (char*)malloc(cap*(sizeof(char)));
    null_check(tmp);
    strcpy(tmp, char_arr);

    *ret_str = (string){
        .size = len, 
        .capacity = cap,
        .string_array = tmp
    };

    return ret_str;
}

char get_elem(string* str, size_t pos){
    assert(pos < str->size);

    return str->string_array[pos];
}

//has no NULL cheacking
string* get_slice(string* str, size_t start, size_t n){
    char* tmp = (char*)malloc(n*sizeof(char));
    null_check(tmp);
    strncpy(tmp, str->string_array + start, n);
    return string_init(tmp);
}

void print_string(string* str){
    printf("Size: %u\nCapacity: %u\nChar_arr: %s\n", str->size, str->capacity, str->string_array);
}

//destruction
void free_string(string* str){
    free(str->string_array);
}

#endif