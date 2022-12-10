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

void null_check(void* ptr, int line, char* file){
    if (ptr == NULL){
        printf("Error: nullable pointer at %d line in file %s", line, file);
    }
}

void string_resize(string* str){
    str->capacity *= 2;
    str->string_array = (char*)realloc(str->string_array, str->capacity);
    null_check(str->string_array, __LINE__, __FILE__);
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
    null_check(ret_str, __LINE__, __FILE__);

    size_t cap = define_capacity(len);
    char* tmp = (char*)malloc(cap*(sizeof(char)));
    null_check(tmp, __LINE__, __FILE__);
    strcpy(tmp, char_arr);

    *ret_str = (string){
        .size = len, 
        .capacity = cap,
        .string_array = tmp
    };

    if (len == 0){
        ret_str->string_array[0] = '\0';
    }

    return ret_str;
}

char get_char(string* str, size_t pos){
    assert(pos < str->size);

    return str->string_array[pos];
}

int char_index(string* str, const char ch){
    for(size_t i = 0; i < str->size; i++){
        if (get_char(str, i) == ch){
            return i;
        }
    }
    return -1;
}

string* char_remove(string* str, char ch){
    char buf[str->size];
    int ch_index = char_index(str, ch);
    if (ch_index == -1){
        return str;
    }
    strncpy(buf, str->string_array, ch_index);
    strncpy(buf + ch_index, str->string_array + ch_index + 1, str->size - ch_index - 1);
    buf[str->size - 1] = '\0';
    free_string(str);
    return string_init(buf);
}

string* char_insert(string* str, char ch, size_t pos){
    char buf[str->size + 1];
    strncpy(buf, str->string_array, pos);
    buf[pos] = ch;
    strncpy(buf + pos + 1, str->string_array + pos, str->size - pos);
    free_string(str);
    return string_init(buf);
}

void print_string(string* str){
    printf("Size: %u\nCapacity: %u\nChar_arr: %s\n", str->size, str->capacity, str->string_array);
}

//destruction of string
void free_string(string* str){
    free(str->string_array);
    free(str);
}

#endif