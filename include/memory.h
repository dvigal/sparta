#ifndef H_MEMORY
#define H_MEMORY

#include "types.h"

typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;

phys_addr_t get_kernel_start_addr(void);

phys_addr_t get_kernel_end_addr(void);

size_t get_kernel_size(void);

/*
 * TODO: replace me
 */
void memset(uint8_t *dest, uint8_t val, uint32_t len);

/*
 * TODO: replace me
 */
void *memcpy(void* destination, const void* source, uint64_t size);

/*
 * Invalidates the translation lookaside buffer (TLB) entry specified with the source operand.
 */
void invalidate_tlb(virt_addr_t vaddr);

phys_addr_t kmalloc(size_t size);

#endif