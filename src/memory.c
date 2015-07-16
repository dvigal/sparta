#include "memory.h"

/*
 * kernel_phys_address_start and kernel_phys_address_end are defined in the link.ld file
 */

extern phys_addr_t kernel_phys_address_start;
extern phys_addr_t kernel_phys_address_end;

//phys_addr_t placement_address = 0x1000 + 0x1000000;
#define KERNEL_START        ((phys_addr_t) &kernel_phys_address_start)
#define KERNEL_END          ((phys_addr_t) &kernel_phys_address_end)
#define KERNEL_SIZE         (KERNEL_END - KERNEL_START)
#define KERNEL_HEAP_START   (KERNEL_END)

phys_addr_t placement_address = 0x1000 + 0x1000000;

static phys_mblock_t free_mblock;

phys_addr_t get_kernel_start_addr(void)
{
    return KERNEL_START;
}

phys_addr_t get_kernel_end_addr(void)
{
    return KERNEL_END;
}

phys_addr_t get_kernel_heap_addr(void)
{
    return KERNEL_HEAP_START;
}

size_t get_kernel_size(void)
{
    return KERNEL_SIZE;
}

phys_addr_t kmalloc_base(size_t size, bool align)
{
  if (align && (placement_address & 0xFFFFF000)) {
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  phys_addr_t addr = placement_address;
  placement_address += size;
  return addr;
}

void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
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

phys_addr_t kmalloc(size_t size)
{
    return kmalloc_base(size, false);
}

void invalidate_tlb(virt_addr_t vaddr) 
{
    asm volatile ("invlpg (,%0,)"::"a"(vaddr));
}