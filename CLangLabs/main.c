#include "string_array.h"
#include <stdio.h>
#include "funcs.h"

int main(int argc, char** argv){
    

    // FILE* file = fopen("test.txt", "r");
    // string* str = read(file);
    // string_array* lines = split(str, "\n");
    // string_array** words = (string_array**)malloc(sizeof(string_array*)*(lines->size));
    // string_array* new_lines = string_array_init(0);
    // for(size_t i = 0; i < lines->size; i++){
    //     words[i] = split(&lines->string_ptr[i], " ");
    //     append_in_array(new_lines, string_compile(words[i]));
    // }
    // print_string_array(lines);
    // print_string_array(new_lines);

    string* str = string_init("213423");
    str = char_insert(str, 't', 3);

    print_string(str);

    return 0;
}