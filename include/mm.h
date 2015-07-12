#ifndef MM_H
#define	MM_H

#include "paging.h"
#include "memory.h"
#include "types.h"

phys_mblock_t *alloc(size_t size);

phys_mblock_t *free(phys_addr_t paddr);

void init_mmanager(phys_addr_t base);

#endif	/* MM_H */

