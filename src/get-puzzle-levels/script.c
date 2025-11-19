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
    int  operationCount;
} PuzzleLevel;

static char *puz_ops0[] = {"AND 0000", "OR 0001", "NOT", "XOR 0010", "SHL 1", "SHR 1"};
static char *puz_ops1[] = {"AND 0010", "OR 0100", "NOT", "XOR 0110", "SHL 1", "SHR 1"};
static char *puz_ops2[] = {"AND 0100", "OR 1000", "NOT", "XOR 1100", "ROL 1", "SHR 1"};
static char *puz_ops3[] = {"AND 1000", "OR 0001", "NOT", "XOR 1001", "SHL 1", "SHR 1"};
static char *puz_ops4[] = {"AND 00000001", "OR 00010000", "NOT", "XOR 00010001", "SHL 1", "SHR 1"};
static char *puz_ops5[] = {"AND 00010000", "OR 00100000", "NOT", "XOR 00110000", "SHL 1", "SHR 1"};
static char *puz_ops6[] = {"AND 0000000000000001", "OR 0000000000010000", "NOT", "XOR 0000000000010001", "SHL 1", "SHR 1"};

static PuzzleLevel puzzle_levels[] = {
    {1, 4, "What's up boss?", "Level 1", "0000", "0001", puz_ops0, 6},
    {2, 4, "You're still good?", "Level 2", "0010", "0100", puz_ops1, 6},
    {3, 4, "It keeps getting harder!", "Level 3", "0100", "1000", puz_ops2, 6},
    {4, 4, "It keeps getting harder!", "Level 4","1000", "0001", puz_ops3, 6},
    {5, 8, "Two Bytes!", "Level 5", "00000001", "00010000", puz_ops4, 6},
    {6, 8,  "You're dead boss?", "Level 6","00010000", "00100000", puz_ops5, 6},
    {7, 16, "Integers?!!?!", "Level 7", "0000000000000001", "0000000000010000", puz_ops6, 6}
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
int getPuzzleLevelOperationCount(int index) {
    return puzzle_levels[index].operationCount;
}

char* getPuzzleLevelOperations(int index) {
    PuzzleLevel *lvl = &puzzle_levels[index];
    int totalLen = 0;
    for (int i = 0; i < lvl->operationCount; i++) {
        totalLen += strlen(lvl->operation_set[i]) + 1; 
    }

    char *buffer = (char*)malloc(totalLen);
    buffer[0] = 0;

    for (int i = 0; i < lvl->operationCount; i++) {
        strcat(buffer, lvl->operation_set[i]);
        if (i < lvl->operationCount - 1) strcat(buffer, ",");
    }

    return buffer;
}

int main() {
    return 0;
}
