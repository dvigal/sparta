#include "memory.h"


void *memset(void *dest, unsigned char value, int count) {
  char *end_addr = dest + count;
  char *tmp = (char *)dest;
  while(tmp < end_addr) {
    *tmp = value;
    tmp++;
  }
}

/*

void* memcpy( void* d, const void* s, unsigned int n ) {
    char* dest;
    char* src;

    dest = ( char* )d;
    src = ( char* )s;

    while ( n-- ) {
        *dest++ = *src++;
    }

    return d;
}
*/