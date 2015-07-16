#ifndef MM_H
#define	MM_H

#include "system.h"
#include "paging.h"
#include "memory.h"
#include "types.h"

phys_mblock_t *alloc(size_t size);

phys_mblock_t *free(phys_addr_t paddr);

void init_mmanager(kinfo_t *kinfo);

#endif	/* MM_H */

