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
string_array string_array_init(size_t n, ...){
    va_list string_list;
    va_start(string_list, n);

    string_array str_arr = (string_array)
    {
        .size = n,
        .capacity = define_capacity(n),
        .string_ptr = (string*)malloc(n*(sizeof(string)))
    };

    for(int i = 0; i < n; i++){
        str_arr.string_ptr[i] = va_arg(string_list, string);
    }

    va_end(string_list);
    return str_arr;
}

void print_string_array(string_array str_arr){
    for (int i = 0; i < str_arr.size; i++){
        printf("%d:\n", i);
        print_string(str_arr.string_ptr[i]);
        printf("\n");
    }
}


#endif