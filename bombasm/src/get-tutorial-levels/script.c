#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>   
// #include <emscripten.h>

struct tutorial_level {
    char *label;
    char *title;
    int  *bit_array;
    char **operation_set;
    char *instruction;
}; 

struct tutorial_level create_tutorial_level(char *level_label, char *level_title, int *bit_array_ptr, 
                                            char **operation_set_ptr,  char *instruction) {
    struct tutorial_level level;
    level.label = level_label;
    level.title = level_title;
    level.bit_array = bit_array_ptr;
    level.operation_set = operation_set_ptr;
    level.instruction = instruction;
    return level;
}

int main() {    

    int list_size = 1;
    struct tutorial_level *ptr = malloc(sizeof(struct tutorial_level) * list_size);
    
    int *bits0 = malloc(sizeof(int) * 2);
    bits0[0] = 1;
    bits0[1] = 1;

    char **ops0 = malloc(sizeof(char*) * 4);
    ops0[0] = "AND 00";
    ops0[1] = "AND 01";
    ops0[2] = "AND 10";
    ops0[3] = "AND 11";

    ptr[0] = create_tutorial_level (
        "AND",
        "AND Operator",
        bits0,
        ops0,
        "This is the AND Operator."
    );

    return 0;

}
