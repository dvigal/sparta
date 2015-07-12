#ifndef PAGING_H
#define PAGING_H

#include "types.h"
#include "memory.h"

#define PAGE_SIZE   0x1000 // 4-KByte Page

// Page directory entries flags. Intel 64 and 32 architectures software developers manual, volume 3a, part 1, pp 3-30..3-33.
#define PAGE_PRESENT(v)            ((true) ? (0x1) : (0x0))
#define PAGE_RW(v)                 ((true) ? (0x1) : (0x0))
#define PAGE_SUPERVISOR(v)         ((true) ? (0x0) : (0x1))
#define PAGE_PRESENT_RW_USER    0x7

#define TABLE_INDEX(vaddr)    (vaddr >> 22)
#define PAGE_INDEX(vaddr)     ((vaddr >> 12) & 0x3FF)    
#define PAGE_PHYSICAL_BASE_ADDRESS(paddr)    (paddr >> 12)

// Page-Table Entry (4-KByte Page). See Intel 64 and 32 achitectures software developers manual.
struct page_struct {
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t user_superuser :   1;
    uint32_t write_through   :   1;
    uint32_t cache_disabled :   1;
    uint32_t accessed       : 1;
    uint32_t dirty          : 1;
    uint32_t page_table_attr_index  :   1;
    uint32_t global_page    :   1;
    uint32_t available      : 3;
    uint32_t baddress    : 20; // Physical address of first by of a 4-KByte page
}__attribute__((packed));
typedef struct page_struct page_t;

struct page_table {
  page_t page[1024];
}__attribute__((packed));
typedef struct page_table page_table_t;

struct page_directory {
  page_table_t *table[1024];
  phys_addr_t tbaddress[1024]; // Page-Table Base Address and Flags
  phys_addr_t address;
}__attribute__((packed));
typedef struct page_directory page_directory_t;

void init_paging();

/*
 * The phisical address of the passed page directory
 * to be loaded in the page directory base regsiter (also PDBR)
 */
void load_page_directory(page_directory_t *pagedir);

page_t *get_page(virt_addr_t vaddr, page_directory_t *dir);

page_directory_t *get_current_page_directory();

void tmp_mappage();

#endif