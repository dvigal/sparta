#ifndef MM_H
#define	MM_H

#include "paging.h"
#include "memory.h"
#include "types.h"


struct phys_memory_block {
    bool type;
    phys_addr_t adderss;
    size_t size;
    struct phys_memory_block *prev;
    struct phys_memory_block *next;
}__attribute__((packed));
typedef struct phys_memory_block phys_mblock_t;

phys_mblock_t *alloc(size_t size);

phys_mblock_t *free(phys_addr_t paddr);

void init_mmanager(void);

#endif	/* MM_H */

