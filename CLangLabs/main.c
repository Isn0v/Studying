#include "string_array.h"
#include <stdio.h>
#include "funcs.h"

int main(int argc, char** argv){
    string_array* str_arr;
    str_arr = string_array_init(
        0
    );

    string* str = string_init("hbsdvhvb dnsnv\njdsjbv, 943ybvd");
    str_arr = split(str);

    print_string_array(str_arr);
    


    return 0;
}