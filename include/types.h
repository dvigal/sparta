#ifndef H_TYPES
#define H_TYPES

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;

typedef const char* string;

typedef uint32_t size_t;

typedef enum { 
  false = 0,
  true = 1
} bool;

#define NONE (void*)0

#endif