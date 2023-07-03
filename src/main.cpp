#include "my-malloc.h"
#include <bits/stdc++.h>

int main() {
  constexpr int SIZE{10};
  int *arr = (int *)myMalloc(SIZE * sizeof(int));
  for (int i = 0; i < SIZE; i++) {
    arr[i] = 10 - i;
  }
  for (int i = 0; i < SIZE; i++) {
    assert(arr[i] == 10 - i);
  }
  auto block = getHeader((void *)arr);
  assert(block->size == 40);
  assert(block->used == true);

  int *arr2 = (int *)myMalloc(5 * sizeof(int));
  block = getHeader((void *)arr2);
  assert(block->used == true);
  myFree(arr);
  myFree(arr2);

  arr = (int *)myMalloc(SIZE * sizeof(int));
  block = getHeader((void *)arr);
  myFree(arr);

  myMalloc(8);
  myMalloc(8);
  myMalloc(8);
  auto o1 = myMalloc(16);
  auto o2 = myMalloc(16);
  myFree(o1);
  myFree(o2);
  auto o3 = myMalloc(16);
  assert(searchStart == getHeader(o3));

  return 0;
}
