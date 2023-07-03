#include "my-malloc.h"
#include <unistd.h>

inline size_t align(size_t n) {
  return (n + sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1);
}

inline size_t allocSize(size_t size) { return size + sizeof(MemBlock); }

void *getMemFromOS(size_t size) {
  size = align(size);

  auto block = (MemBlock *)sbrk(0);
  if (sbrk(allocSize(size)) == (void *)-1) {
    return nullptr;
  }

  return block;
}

MemBlock *nextFitSearch(size_t size) {
  while (searchStart != nullptr) {
    if (searchStart->used || searchStart->size < size) {
      searchStart = searchStart->next;
      continue;
    }

    return searchStart;
  };
  searchStart = heapStart;
  return nullptr;
}

MemBlock *firstFitSearch(size_t size) {
  auto block = heapStart;
  while (block != nullptr) {
    if (block->used || block->size < size) {
      block = block->next;
      continue;
    }

    return block;
  };
  return nullptr;
}

MemBlock *findBlock(size_t size) {
  switch (searchMode) {
  case SearchMode::FirstFit:
    return firstFitSearch(size);
  case SearchMode::NextFit:
    return nextFitSearch(size);
  }
  return nullptr;
}

void *myMalloc(size_t size) {
  size = align(size);
  if (auto block = findBlock(size)) {
    block->used = true;
    return block->data;
  }

  auto block = (MemBlock *)getMemFromOS(size);
  block->size = size;
  block->used = true;

  if (heapStart == nullptr) {
    heapStart = block;
    searchStart = block;
  }
  if (heapTop != nullptr) {
    heapTop->next = block;
  }
  heapTop = block;

  return block->data;
}
