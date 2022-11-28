#ifndef MY_FUNCS_LIB_H
#define MY_FUNCS_LIB_H

#include "string_array.h"


string_array* split(string* str){
    size_t start_pos = 0;
    char ch;

    string_array* str_arr = string_array_init(0);
    string* tmp;

    for(size_t i = 0; i < str->size; i++){
        ch = get_elem(str, i);
        if (ch == ' ' || ch == '\n'){
            tmp = get_slice(str, start_pos, i);
            null_check(tmp);
            append_in_array(str_arr, tmp);
            start_pos = i + 1;
        }
    }
    return str_arr;
}



#endif MY_FUNCS_LIB_H