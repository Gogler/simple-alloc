#pragma once

#include <cstdint>
#include <unistd.h>

struct MemBlock {
  size_t size;
  bool used;
  MemBlock *next;
  uintptr_t data[0];
};

enum SearchMode {
  FirstFit,
  NextFit,
  PerfectFit,
};

extern MemBlock *heapTop;
extern MemBlock *heapStart;
extern MemBlock *searchStart;

extern SearchMode searchMode;

void *myMalloc(size_t size);
void myFree(void *data);

inline MemBlock *getHeader(void *data) {
  return reinterpret_cast<MemBlock *>((uintptr_t)data - sizeof(MemBlock));
}
