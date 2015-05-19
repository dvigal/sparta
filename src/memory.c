#include "memory.h"


void *memset(void *dest, uint8_t value, uint64_t size) 
{
  uint8_t *end_addr = dest + size;
  uint8_t *tmp = (char *)dest;
  while(tmp < end_addr) {
    *tmp = value;
    tmp++;
  }
}

void *memcpy(void* destination, const void* source, uint64_t size)
{
    uint8_t *dest = (uint8_t*) destination;
    uint8_t *src = (uint8_t*) source;
    while (size--) {
        *dest++ = *src++;
    }
    return destination;
}