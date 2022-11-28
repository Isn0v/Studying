#ifndef STRING_ARRAY_LIB_H
#define STRING_ARRAY_LIB_H

#include <stdarg.h>
#include "my_string.h"

typedef struct String_array{
    size_t size;
    size_t capacity;
    string* string_ptr;

} string_array;

//Init
string_array* string_array_init(size_t n, ...){
    string_array* str_arr = (string_array*)malloc(sizeof(string_array));
    null_check(str_arr);

    va_list string_list;
    va_start(string_list, n);
    
    size_t cap = define_capacity(n);

    *str_arr = (string_array){
        .size = n,
        .capacity = cap,
        .string_ptr = (string*)malloc(cap*(sizeof(string)))
    };

    null_check(str_arr->string_ptr);

    for(size_t i = 0; i < n; i++){
        str_arr->string_ptr[i] = va_arg(string_list, string);
    }

    va_end(string_list);
    return str_arr;
}

void string_array_resize(string_array* str_arr){
    str_arr->capacity *= 2;
    str_arr->string_ptr = (string*)realloc(str_arr->string_ptr, str_arr->capacity*sizeof(string));
    null_check(str_arr->string_ptr);
}

void append_in_array(string_array* str_arr, string* str){
    size_t cur_size = str_arr->size;
    size_t cur_cap = str_arr->capacity;

    if (cur_size + 1 > cur_cap){
        string_array_resize(str_arr);
    }
    str_arr->string_ptr[cur_size] = *str;
    str_arr->size += 1;
}

void free_string_array(string_array* str_arr){
    for(size_t i = 0; i < str_arr->size; i++){
        free_string(&(str_arr->string_ptr[i]));
    }
    free(str_arr);
}

void print_string_array(string_array* str_arr){
    for (size_t i = 0; i < str_arr->size; i++){
        printf("%d:\n", i);
        print_string(&(str_arr->string_ptr[i]));
        printf("\n");
    }
}


#endif