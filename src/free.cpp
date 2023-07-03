#include "my-malloc.h"

void myFree(void *data) {
  auto block = getHeader(data);
  block->used = false;
}
