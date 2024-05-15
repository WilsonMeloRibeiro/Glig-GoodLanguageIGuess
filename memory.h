#ifndef glig_memory_h
#define glig_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, pointer, oldCapacity, capacity) (type *)allocateMemory(pointer, sizeof(type) * (oldCapacity), sizeof(type) * (capacity))
#define FREE_ARRAY(type, pointer, oldCapacity) allocateMemory(pointer, sizeof(type) * (oldCapacity), 0)

void *allocateMemory(void *pointer, size_t oldSize, size_t size);
#endif