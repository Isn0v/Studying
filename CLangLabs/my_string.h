#ifndef MY_STRING_LIB_H
#define MY_STRING_LIB_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct String{
    size_t size;
    size_t capacity;
    char* string_array;
} string;

void resize_capacity(string str){
    str.capacity *= 2;
    str.string_array = (char*)realloc(str.string_array, str.capacity);
}

size_t define_capacity(size_t n){
    size_t iter = 1;
    while (iter < n)
    {
        iter *= 2;
    }
    return iter;
}

//initialization
string string_init(char* char_arr){
    size_t len = strlen(char_arr);

    string ret_str = (string)
    {
        .size = len, 
        .capacity = define_capacity(len), 
        .string_array = char_arr
    };

    return ret_str;
}

void print_string(string str){
    printf("Size: %u\nCapacity: %u\nChar_arr: %s\n", str.size, str.capacity, str.string_array);
}

//length of array of strings
size_t strings_len(string* str_arr){
    return (size_t)(sizeof(str_arr)/sizeof(string));
}

//destruction
void string_destruct(string str){
    free(str.string_array);
}

#endif