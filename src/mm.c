#include "mm.h"

phys_mblock_t *current_mblock;

void init_mmanager()
{
    current_mblock = (phys_mblock_t*) kmalloc(sizeof(phys_mblock_t));
    //current_mblock->adderss = get_page();
}
