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

    ptr[1] = create_tutorial_level (
        "OR",
        "OR Operator",
        bits0,
        ops0,
        "This is the OR Operator."
    )

    ptr[2] = create_tutorial_level (
        "XOR",
        "XOR Operator",
        bits0,
        ops0,
        "This is the XOR Operator."
    )

    ptr[3] = create_tutorial_level (
        "SHL",
        "SHL Operator",
        bits0,
        ops0,
        "This is the SHL Operator."
    )

    ptr[4] = create_tutorial_level (
        "SHR",
        "SHR Operator",
        bits0,
        ops0,
        "This is the SHR Operator."
    )

    ptr[5] = create_tutorial_level (
        "ROL",
        "ROL Operator",
        bits0,
        ops0,
        "This is the ROL Operator."
    )

    ptr[6] = create_tutorial_level (
        "ROR",
        "ROR Operator",
        bits0,
        ops0,
        "This is the ROR Operator."
    )

    return 0;

}


void stringToUpper(char *str) {
    char *ptr = str;
    while (*ptr) {
        *ptr = toupper((unsigned char)*ptr);
        ptr++;
    }
}

EMSCRIPTEN_KEEPALIVE
int bitStringOperations(int a, int b, char *op) {
    int result = 0;
    stringToUpper(op);

    if (strcmp(op, "AND") == 0) {
        result = a & b;
    } else if (strcmp(op, "OR") == 0) {
        result = a | b;
    } else if (strcmp(op, "XOR") == 0) {
        result = a ^ b;
    } else if (strcmp(op, "NOT") == 0) {
        result = ~a;
    } else if (strcmp(op, "SHL") == 0) {
        result = a << b;
    } else if (strcmp(op, "SHR") == 0) {
        result = a >> b;
    } else if (strcmp(op, "ROL") == 0) {
        result = (a << b) | (a >> (32 - b));
    } else if (strcmp(op, "ROR") == 0) {
        result = (a >> b) | (a << (32 - b));
    } else {
        result = 0;  // unknown op
    }

    return result;
}