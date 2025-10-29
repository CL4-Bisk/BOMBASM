#include <stdio.h>
#include <emscripten.h>


EMSCRIPTEN_KEEPALIVE
int addNum(int a, int b) {
  return a + b;
}

EMSCRIPTEN_KEEPALIVE
int main(int argc, char** argv) {
  printf("hello, world!\n");
  return 0;
}