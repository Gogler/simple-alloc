#include "my-malloc.h"
#include <cstdint>
#include <unistd.h>

using namespace std;

MemBlock *heapTop = nullptr;
MemBlock *heapStart = nullptr;
MemBlock *searchStart = nullptr;

SearchMode searchMode = NextFit;
