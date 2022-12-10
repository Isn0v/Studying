#ifndef MY_FUNCS_LIB_H
#define MY_FUNCS_LIB_H

#include "string_array.h"
#include <ctype.h>

int degree(int num, int deg){
    int res_num = 1;
    for(size_t i = 0; i < deg; i++){
        res_num *= num;
    }
    return res_num;
}

char is_calc_operator(char ch){
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*'){
        return 1;
    } else {
        return 0;
    }
}


string* delete_brackets(string* str){
    while (1){
    int open_bracket_index = char_index(str, '(');
    int close_bracket_index = char_index(str, ')');
        if(open_bracket_index != -1 && 
            close_bracket_index != -1){
                str = char_remove(str, '(');
                str = char_remove(str, ')');
        } else {
            break;
        }
    }
    return str;
}

//making ' ' after '(' and before ')'
string* brackets_normallize(string* str){
    int open_bracket_index = char_index(str, '(');
    if (get_char(str, open_bracket_index + 1) == ' '){
        open_bracket_index = -1;
    }
    int close_bracket_index = char_index(str, ')');

    while(1){
        if (open_bracket_index != -1 && get_char(str, open_bracket_index + 1) != ' '){
            str = char_insert(str, ' ', open_bracket_index + 1);
        }
        if (close_bracket_index != -1 && get_char(str, close_bracket_index + 1) != ' '){
            str = char_insert(str, ' ', close_bracket_index - 1);
        }
    }
    return str;
}

//without free_string()
string_array* split(string* str, const char* delim){
    string_array* str_arr = string_array_init(0);

    //normallization of numbers of new lines
    if(str->size >= 3){
        for(size_t i = 0; i < str->size - 2; i++){
            if (get_char(str, i) == '\n' && get_char(str, i + 1) == '\n' && get_char(str, i + 2) != '\n'){
                char res_buf[str->size + 1];

                strncpy(res_buf, str->string_array, i + 1);
                res_buf[i + 1] = ' ';
                strncpy(res_buf + i + 2, str->string_array + i + 1, str->size - i);
                res_buf[str->size] = '\0';

                str = string_init(res_buf);
            }
        }
    }
    str = brackets_normallize(str);

    char* tmp = strtok(str->string_array, delim);
    while (tmp != NULL){
        append_in_array(str_arr, string_init(tmp));
        tmp = strtok(NULL, delim);
    }
    return str_arr;
}

string* fars_to_cels(string* fareign){
    if (fareign->size > 3 && fareign->size <= 10 && (get_char(fareign, 0) == '+' || get_char(fareign, 0) == '-')
    && get_char(fareign, fareign->size - 2) == 't' && get_char(fareign, fareign->size - 1) == 'F'){
        for (size_t i = 1; i < fareign->size - 2; i++){
            if (!isdigit(get_char(fareign, i))){
                return fareign;
            }
        }

        size_t num_rank = fareign->size - 3;
        double fars = 0; 
        for (size_t i = 1; i < fareign->size - 2; i++){
            fars += (get_char(fareign, i) - 48) * degree(10, num_rank - i);
        }
        double celsiums = 5 * (fars - 32) / 9;
        char cels[10];

        if (celsiums < 0){
            sprintf(cels, "-%.1ftC", celsiums);
        } else {
            sprintf(cels, "%.1ftC", celsiums);
        }
        
        free_string(fareign);
        return string_init(cels);
    } else {
        return fareign;
    }
}

string* palindrom(string* str){
    size_t str_size = str->size;
    for(size_t i = 0; i < str_size / 2 + 1; i++){
        if (get_char(str, i) != get_char(str, str_size - i - 1)){
            return str;
        }
    }
    free_string(str);
    return string_init("PALINDROM");
}

string* read(FILE* file){
    size_t MAX_COUNT = 4;
    char* buff = (char*)malloc(sizeof(char)*MAX_COUNT);
    null_check(buff, __LINE__, __FILE__);

    char ch = getc(file);
    size_t ind = 0;
    buff[ind] = ch;
    while (1){
        ch = getc(file);
        if (++ind == MAX_COUNT){
            MAX_COUNT *= 2;
            buff = realloc(buff, sizeof(char)*(MAX_COUNT + 1));
            null_check(buff, __LINE__, __FILE__);
        }
        if (ch == EOF){
            break;
        }
        buff[ind] = ch;
    }
    buff[ind] = '\0';

    string* str = string_init(buff);
    free(buff);
    return str;
}

string* string_compile(string_array* str_arr){
    size_t size = str_arr->size - 1;
    for(size_t i = 0; i < str_arr->size; i++){
        size += str_arr->string_ptr[i].size;
    }
    char buf[size];
    size_t buff_pos = 0;
    for(size_t i = 0; i < str_arr->size; i++){
        for(size_t j = 0; j < str_arr->string_ptr[i].size; j++){
            buf[buff_pos++] = str_arr->string_ptr[i].string_array[j];
        }
        buf[buff_pos++] = ' ';
    }
    return string_init(buf);
}



#endif MY_FUNCS_LIB_H