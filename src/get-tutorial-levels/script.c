#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <emscripten/html5.h>
#include <emscripten.h>

typedef struct {
    char *title;
    char *operator;
    int  bitWidth;
    char *startBitstring;
    char **operation_set;
    int opcount;
    char *description;
} TutorialLevel;

static char *ops0[] = {"AND 0", "AND 1"};
static char *ops1[] = {"OR 0", "OR 1"};
static char *ops2[] = {"NOT"};
static char *ops3[] = {"XOR 0", "XOR 1"};
static char *ops4[] = {"SHL 1", "SHR 1", "SHL 2", "SHL 2"};
static char *ops5[] = {"ROL 1", "ROR 1", "ROR 2", "ROR 2"};

static TutorialLevel tutorial_levels[] = {
    {"AND Operator", "AND", 1, "1", ops0, 2, "This is the AND Operator."},
    {"OR Operator",  "OR",  1, "0", ops1, 2, "This is the OR Operator."},
    {"NOT Operator", "NOT", 1, "0", ops2, 1, "This is the NOT Operator."},
    {"XOR Operator", "XOR", 1, "0", ops3, 2, "This is the XOR Operator."},
    {"Shift Operators", "SHL, SHR", 8, "01000101", ops4, 4, "These are the Shift Operators."},
    {"Rotate Operators", "ROL, ROR", 8, "01000101", ops5, 4, "These are the Rotate Operators."},
};

EMSCRIPTEN_KEEPALIVE
int getTutorialLevelCount() {
    return sizeof(tutorial_levels) / sizeof(tutorial_levels[0]);
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelTitle(int index) {
    return tutorial_levels[index].title;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelOperator(int index) {
    return tutorial_levels[index].operator;
}

EMSCRIPTEN_KEEPALIVE
int getTutorialLevelBitWidth(int index) {
    return tutorial_levels[index].bitWidth;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelStartBitstring(int index) {
    return tutorial_levels[index].startBitstring;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelDescription(int index) {
    return tutorial_levels[index].description;
}

char* getTutorialLevelOperations(int index) {
    TutorialLevel *lvl = &tutorial_levels[index];

    int totalLen = 0;
    for (int i = 0; i < lvl->opcount; i++) {
        totalLen += strlen(lvl->operation_set[i]);
    }
    totalLen += lvl->opcount; 

    char *buffer = (char*)malloc(totalLen);
    buffer[0] = '\0';

    for (int i = 0; i < lvl->opcount; i++) {
        strcat(buffer, lvl->operation_set[i]);
        if (i < lvl->opcount - 1) strcat(buffer, ",");
    }

    return buffer;
}

int main() {    
    return 0;
}
