#include "string_array.h"
#include <stdio.h>
#include "funcs.h"

int main(int argc, char** argv){
    

    FILE* file = fopen("test.txt", "r");
    string* str = read(file);
    string_array* lines = split(str, "\n");
    string_array** words = (string_array**)malloc(sizeof(string_array*)*(lines->size));
    for(size_t i = 0; i < lines->size; i++){
        words[i] = split(&lines[i], " ");
        lines[i] = string_compile(words[i]);
    }
    print_string_array(lines);
    return 0;
}