#ifndef H_PAGING
#define H_PAGING

#include "types.h"

#define VM_PAGE_SIZE    4 * 1024 // PAGE SIZE
#define VM_PT_ENTRIES   1024 // PAGE TABLE ENTRIES
#define VM_PD_SIZE  (VM_PAGE_SIZE * VM_PT_ENTRIES) // PAGE DIRECTORY SIZE

// Page directory entries flags. Intel 64 and 32 architectures software developers manual, volume 3a, part 1, pp 3-30..3-33
#define VM_PT_PRESENT   0x0001
#define VM_PT_READ      0x0000
#define VM_PT_RW        0x0010
#define VM_PT_USER      0x0100
#define VM_PT_PWT       0x1000
#define VM_PT_PCD       0x10000
#define VM_PT_ACCESSED  0x100000

struct page_struct {
  uint32_t present 	: 1;
  uint32_t rw		: 1;
  uint32_t user		: 1;
  uint32_t accessed	: 1;
  uint32_t dirty	: 1;
  uint32_t unused	: 7;
  uint32_t frame	: 20;
}__attribute__((packed));
typedef struct page_struct page_t;

struct page_table {
  page_t pages[1024];
}__attribute__((packed));
typedef struct page_table page_table_t;

struct page_directory {
  page_table_t *tables[1024];
  uint32_t tablesPhysical[1024];
  uint32_t phyicalAddr;
}__attribute__((packed));
typedef struct page_directory page_directory_t;

uint32_t map_kernel();

uint32_t get_kernel_phys_address();

uint32_t get_kernel_phys_address_end();

uint32_t get_kernel_length();

void init_paging();

void load_page_directory(page_directory_t *pagedir);

#endif