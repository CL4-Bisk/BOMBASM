#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>   
// #include <emscripten.h>

// struct tutorial_level {
//     char *label;
//     char *title;
//     int  *bit_array;
//     char **operation_set;
//     char *instruction;
// }; 

struct PuzzleLevel{
    int  levelNumber;
    int  bitWidth;
    char *startBitstring;
    char *goalBitstring;
    char **operation_set;
    int  operationCount;
};

PuzzleLevel puzzle_levels[7];

puzzle_levels[0].levelNumber = 1;
puzzle_levels[0].bitWidth = 4;
puzzle_levels[0].startBitstring = "0000";
puzzle_levels[0].goalBitstring = "0001";
char *puz_ops0[] = {"AND 0000", "OR 0001", "NOT 0001", "XOR 0010", "SHL 0001", "SHR 0001"};
puzzle_levels[0].operation_set = puz_ops0;
puzzle_levels[0].operationCount = 5;

puzzle_levels[1].levelNumber = 2;
puzzle_levels[1].bitWidth = 4;
puzzle_levels[1].startBitstring = "0010";
puzzle_levels[1].goalBitstring = "0100";
char *puz_ops1[] = {"AND 0010", "OR 0100", "NOT 0100", "XOR 0110", "SHL 0010", "SHR 0010"};
puzzle_levels[1].operation_set = puz_ops1;
puzzle_levels[1].operationCount = 5;

puzzle_levels[2].levelNumber = 3;
puzzle_levels[2].bitWidth = 4;
puzzle_levels[2].startBitstring = "0100";
puzzle_levels[2].goalBitstring = "1000";
char *puz_ops2[] = {"AND 0100", "OR 1000", "NOT 1000", "XOR 1100", "SHL 0100", "SHR 0100"};
puzzle_levels[2].operation_set = puz_ops2;
puzzle_levels[2].operationCount = 5;

puzzle_levels[3].levelNumber = 4;
puzzle_levels[3].bitWidth = 4;
puzzle_levels[3].startBitstring = "1000";
puzzle_levels[3].goalBitstring = "0001";
char *puz_ops3[] = {"AND 1000", "OR 0001", "NOT 0001", "XOR 1001", "SHL 1000", "SHR 1000"};
puzzle_levels[3].operation_set = puz_ops3;
puzzle_levels[3].operationCount = 5;

puzzle_levels[4].levelNumber = 5;
puzzle_levels[4].bitWidth = 8;
puzzle_levels[4].startBitstring = "00000001";
puzzle_levels[4].goalBitstring = "00010000";
char *puz_ops4[] = {"AND 00000001", "OR 00010000", "NOT 00010000", "XOR 00010001", "SHL 00000001", "SHR 00000001"};
puzzle_levels[4].operation_set = puz_ops4;
puzzle_levels[4].operationCount = 5;

puzzle_levels[5].levelNumber = 6;
puzzle_levels[5].bitWidth = 8;
puzzle_levels[5].startBitstring = "00010000";
puzzle_levels[5].goalBitstring = "00100000";
char *puz_ops5[] = {"AND 00010000", "OR 00100000", "NOT 00100000", "XOR 00110000", "SHL 00010000", "SHR 00010000"};
puzzle_levels[5].operation_set = puz_ops5;
puzzle_levels[5].operationCount = 5;

puzzle_levels[6].levelNumber = 7;
puzzle_levels[6].bitWidth = 16;
puzzle_levels[6].startBitstring = "0000000000000001";
puzzle_levels[6].goalBitstring = "0000000000010000";
char *puz_ops6[] = {"AND 0000000000000001", "OR 0000000000010000", "NOT 0000000000010000", "XOR 0000000000010001", "SHL 0000000000000001", "SHR 0000000000000001"};
puzzle_levels[6].operation_set = puz_ops6;
puzzle_levels[6].operationCount = 5;


struct PuzzleLevel getPuzzleLevel(int index) {
    return puzzle_levels[index];
}

// struct tutorial_level create_tutorial_level(char *level_label, char *level_title, int *bit_array_ptr, 
//                                             char **operation_set_ptr,  char *instruction) {
//     struct tutorial_level level;
//     level.label = level_label;
//     level.title = level_title;
//     level.bit_array = bit_array_ptr;
//     level.operation_set = operation_set_ptr;
//     level.instruction = instruction;
//     return level;
// }

int main() {    

    // int list_size = 1;
    // tutorial_level *ptr = malloc(sizeof(tutorial_level) * list_size);
    
    // int *bits0[2];
    // bits0[0] = 0;
    // bits0[1] = 1;

    // int *bits1[2];
    // bits0[0] = 10;
    // bits0[1] = 11;

    // int *bits2[4];
    // bits0[0] = 100;
    // bits0[1] = 101;
    // bits0[2] = 110;
    // bits0[3] = 111;

    // int *bits3[8];
    // bits0[0] = 1000;
    // bits0[1] = 1001;
    // bits0[2] = 1010;
    // bits0[3] = 1011;
    // bits0[4] = 1100;
    // bits0[5] = 1101;
    // bits0[6] = 1110;
    // bits0[7] = 1111;

    // char **ops0 = malloc(sizeof(char*) * 4);
    // ops0[0] = "AND 00";
    // ops0[1] = "AND 01";
    // ops0[2] = "AND 10";
    // ops0[3] = "AND 11";

    // char **ops1 = malloc(sizeof(char*) * 4);
    // ops1[0] = "OR 00";
    // ops1[1] = "OR 01";
    // ops1[2] = "OR 10";
    // ops1[3] = "OR 11";

    // char **ops2 = malloc(sizeof(char*) * 4);
    // ops2[0] = "XOR 00";
    // ops2[1] = "XOR 01";
    // ops2[2] = "XOR 10";
    // ops2[3] = "XOR 11";

    // char **ops3 = malloc(sizeof(char*) * 4);
    // ops3[0] = "SHL 00";
    // ops3[1] = "SHL 01";
    // ops3[2] = "SHL 10";
    // ops3[3] = "SHL 11";

    // char **ops4 = malloc(sizeof(char*) * 4);
    // ops4[0] = "SHR 00";
    // ops4[1] = "SHR 01";
    // ops4[2] = "SHR 10";
    // ops4[3] = "SHR 11";

    // char **ops5 = malloc(sizeof(char*) * 4);
    // ops5[0] = "ROL 00";
    // ops5[1] = "ROL 01";
    // ops5[2] = "ROL 10";
    // ops5[3] = "ROL 11";

    // char **ops6 = malloc(sizeof(char*) * 4);
    // ops6[0] = "ROR 00";
    // ops6[1] = "ROR 01";
    // ops6[2] = "ROR 10";
    // ops6[3] = "ROR 11";


    // ptr[0] = create_tutorial_level (
    //     // "AND",
    //     // "AND Operator",
    //     // bits0,
    //     // ops0,
    //     // "This is the AND Operator."
    //     "AND Operator",
    //     "AND",
    //     2,
    //     bits0,
    //     ops0,
    //     "This is the AND Operator."
    // );

    // ptr[1] = create_tutorial_level (
    //     "OR Operator",
    //     "OR",
    //     2,
    //     bits0,
    //     ops1,
    //     "This is the OR Operator."
    // )

    // ptr[2] = create_tutorial_level (
    //     "XOR Operator",
    //     "XOR",
    //     2,
    //     bits0,
    //     ops2,
    //     "This is the XOR Operator."
    // )

    // ptr[3] = create_tutorial_level (
    //     "SHL Operator",
    //     "SHL",
    //     2,
    //     bits0,
    //     ops3,
    //     "This is the SHL Operator."
    // )

    // ptr[4] = create_tutorial_level (
    //     "SHR Operator",
    //     "SHR",
    //     2,
    //     bits0,
    //     ops4,
    //     "This is the SHR Operator."
    // )

    // ptr[5] = create_tutorial_level (
    //     "ROL Operator",
    //     "ROL",
    //     2,
    //     bits0,
    //     ops5,
    //     "This is the ROL Operator."
    // )

    // ptr[6] = create_tutorial_level (
    //     "ROR Operator",
    //     "ROR",
    //     2,
    //     bits0,
    //     ops6,
    //     "This is the ROR Operator."
    // )


    // puzzle_level *puz_ptr = malloc(sizeof(puzzle_level) * list_size);

    // puz_ptr[0] = create_puzzle_level (
    //     1,
    //     4,
    //     "0000",
    //     "0001",
    //     ops0,
    //     5
    // )

    // puz_ptr[1] = create_puzzle_level (
    //     2,
    //     4,
    //     "0010",
    //     "0100",
    //     ops1,
    //     5
    // )

    // puz_ptr[2] = create_puzzle_level (
    //     3,
    //     4,
    //     "0100",
    //     "1000",
    //     ops0,
    //     5
    // )


    return 0;

}


// void stringToUpper(char *str) {
//     char *ptr = str;
//     while (*ptr) {
//         *ptr = toupper((unsigned char)*ptr);
//         ptr++;
//     }
// }

// EMSCRIPTEN_KEEPALIVE
// int bitStringOperations(int a, int b, char *op) {
//     int result = 0;
//     stringToUpper(op);

//     if (strcmp(op, "AND") == 0) {
//         result = a & b;
//     } else if (strcmp(op, "OR") == 0) {
//         result = a | b;
//     } else if (strcmp(op, "XOR") == 0) {
//         result = a ^ b;
//     } else if (strcmp(op, "NOT") == 0) {
//         result = ~a;
//     } else if (strcmp(op, "SHL") == 0) {
//         result = a << b;
//     } else if (strcmp(op, "SHR") == 0) {
//         result = a >> b;
//     } else if (strcmp(op, "ROL") == 0) {
//         result = (a << b) | (a >> (32 - b));
//     } else if (strcmp(op, "ROR") == 0) {
//         result = (a >> b) | (a << (32 - b));
//     } else {
//         result = 0;  // unknown op
//     }

//     return result;
// }