#include "string_array.h"
#include <stdio.h>

int main(int argc, char** argv){
    string_array str_arr;
    str_arr = string_array_init(
        5, 
        string_init("Hello!"), 
        string_init("I AM"),
        string_init("THE ONE"),
        string_init("WHO DID THIS"),
        string_init("FOR ALL NIGHT THROUGHOUT")
    );

    print_string_array(str_arr);
    //printf("Size: %u\nCap: %u", str_arr.size, str_arr.capacity);


    return 0;
}