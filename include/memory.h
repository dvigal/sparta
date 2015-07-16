#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

struct phys_memory_block {
    bool type;
    phys_addr_t adderss;
    size_t size;
    struct phys_memory_block *prev;
    struct phys_memory_block *next;
}__attribute__((packed));
typedef struct phys_memory_block phys_mblock_t;

struct phys_memory_info {
    size_t memory_size;
    uint32_t free_page_count;
    phys_mblock_t *base;
};
typedef struct phys_memory_info phys_minfo_t;

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