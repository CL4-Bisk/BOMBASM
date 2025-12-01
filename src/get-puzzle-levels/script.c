#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>   
#include <emscripten.h>

typedef struct {
    int  levelNumber;
    int  bitWidth;
    char  *title;
    char  *subtitle;
    char *startBitstring;
    char *goalBitstring;
    char **operation_set;
    int  operationSize;
    int operationCount;
    char *description;
} PuzzleLevel;

// Level operations
static char *puz_ops0[] = {"NOT", "OR 0010", "AND 0110", "OR 1100"};
static char *puz_ops1[] = {"XOR 1010", "XOR 0000", "XOR 0110", "XOR 0101"};
static char *puz_ops2[] = {"XOR 1101", "OR 0010", "OR 0001", "AND 0100", "OR 1000", "OR 0100"};
static char *puz_ops3[] = {"AND 0000", "SHL 1", "OR 0001"};
static char *puz_ops4[] = {"OR 000111", "OR 000101", "OR 001001", "OR 000011", "OR 000010", "SHL 1"};
static char *puz_ops5[] = {"SHL 2", "SHR 1", "OR 00000011"};
static char *puz_ops6[] = {"NOT", "SHR 2", "SHL 2", "OR 00000001"};
static char *puz_ops7[] = {"ROL 1", "ROR 1", "OR 000100", "AND 101111"};

// Puzzle levels
static PuzzleLevel puzzle_levels[] = {
    {1, 4, "Boolean Operations", "Level 1", "0011", "1001", puz_ops0, 4, 4,
     "Bits and simple boolean operations can create complex results.<br><br>Convert the bitstring on the screen to the target below. Check Tutorial Levels for help."},
    {2, 4, "That's not the OR I know?", "Level 2", "0001", "1000",  puz_ops1, 4, 6,
     "Previous bitshifts were boring, so now all operations are XOR.<br><br>If bits are the same, result 0; if different, result 1.<br>Example: 01 XOR 11 → 10."},
    {3, 4, "Setting to Zero", "Level 3", "1111", "0000", puz_ops2, 6, 4,
     "Sometimes you want all bits to be 0.<br>Use AND with 0000 or XOR to achieve this."},
    {4, 4, "Boolean Operations are Faster!", "Level 4", "0011", "0101", puz_ops3, 3, 6,
     "Bit operations are faster than arithmetic because they don't rely on previous results.<br>They can be done in parallel."},
    {5, 6, "Multiplication", "Level 5", "000000", "101000", puz_ops4, 6, 4,
     "Multiplying by 2 or 4 in binary is just shifting bits left.<br>Shifting is faster than traditional multiplication."},
    {6, 8, "The Assembly Line", "Level 6","00000000", "01011101", puz_ops5, 3, 14,
     "Shifting can cause overflow, but it can be caught by flags.<br>Use all your knowledge from previous levels."},
    {7, 8, "Two's Complement", "Level 8", "01010000", "10110000", puz_ops6, 4, 6,
     "Two’s complement represents negative numbers.<br>Flip all bits and add 1 to get the negative equivalent; however since this machine does not have any addition operations, make it so that it reaches the target bitstring."},
    {8, 6, "Merry Go Round", "Level 9", "101010", "100101", puz_ops7, 4, 12,
     "Rotations loop bits around instead of overflowing.<br>Use ROL and ROR to go to the AND and OR bitmasks."}
};


EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelCount() {
    return sizeof(puzzle_levels) / sizeof(puzzle_levels[0]);
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelNumber(int index) {
    return puzzle_levels[index].levelNumber;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelBitWidth(int index) {
    return puzzle_levels[index].bitWidth;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelTitle(int index) {
    return puzzle_levels[index].title;
} 

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelSubtitle(int index) {
    return puzzle_levels[index].subtitle;
} 

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelStartBitstring(int index) {
    return puzzle_levels[index].startBitstring;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelGoalBitstring(int index) {
    return puzzle_levels[index].goalBitstring;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLeveloperationSize(int index) {
    return puzzle_levels[index].operationSize;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelOpCount(int index) {
    return puzzle_levels[index].operationCount;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelDescription(int index) {
    return puzzle_levels[index].description;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelOperations(int index) {
    PuzzleLevel *lvl = &puzzle_levels[index];
    int totalLen = 0;
    for (int i = 0; i < lvl->operationSize; i++) {
        totalLen += strlen(lvl->operation_set[i]) + 1; 
    }

    char *buffer = (char*)malloc(totalLen);
    buffer[0] = 0;

    for (int i = 0; i < lvl->operationSize; i++) {
        strcat(buffer, lvl->operation_set[i]);
        if (i < lvl->operationSize - 1) strcat(buffer, ",");
    }

    return buffer;
}

int main() {
    return 0;
}
