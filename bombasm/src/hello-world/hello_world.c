#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <emscripten/html5.h>
#include <emscripten.h>


// EMSCRIPTEN_KEEPALIVE
// int addNum(int a, int b) {
//   return a + b;
// }

// EMSCRIPTEN_KEEPALIVE
// int main() {
//   printf("hello, world!\n");
//   return 0;
// }

void stringToUpper(char *str) {
    char *ptr = str;
    while (*ptr) {
        *ptr = toupper((unsigned char)*ptr);
        ptr++;
    }
}

EMSCRIPTEN_KEEPALIVE
uint32_t bitStringOperations(uint32_t a, uint32_t b, char *op, uint8_t bitWidth) {
  uint32_t result = 0;
  uint32_t mask;

  switch (bitWidth) {
      case 4:
          mask = 0xF;        // 0000 1111
          break;
      case 8:
          mask = 0xFF;       // 1111 1111
          break;
      case 16:
          mask = 0xFFFF;     // 16 bits
          break;
      case 32:
      default:
          mask = 0xFFFFFFFF; // 32 bits
          break;
  }

  a &= mask;
  b &= mask;

  stringToUpper(op);

  if (strcmp(op, "AND") == 0) {
      result = a & b;
  } else if (strcmp(op, "OR") == 0) {
      result = a | b;
  } else if (strcmp(op, "XOR") == 0) {
      result = a ^ b;
  } else if (strcmp(op, "NOT") == 0) {
      result = ~a & mask; // re-mask to remove extra bits
  } else if (strcmp(op, "SHL") == 0) {
      result = (a << b) & mask;
  } else if (strcmp(op, "SHR") == 0) {
      result = (a >> b) & mask;
  } else if (strcmp(op, "ROL") == 0) {
      uint8_t shift = b % bitWidth; // prevent over-rotation (maguba ang rotate)
      result = ((a << shift) | (a >> (bitWidth - shift))) & mask;
  } else if (strcmp(op, "ROR") == 0) {
      uint8_t shift = b % bitWidth;
      result = ((a >> shift) | (a << (bitWidth - shift))) & mask;
  } else {
      result = 0; // invalid op
  }

  return result;
}