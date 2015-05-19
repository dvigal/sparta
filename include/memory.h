#ifndef H_MEMORY
#define H_MEMORY

#include "types.h"

void *memset(void *dest, uint8_t value, uint64_t size);

void *memcpy(void* destination, const void* source, uint64_t size);

#endif