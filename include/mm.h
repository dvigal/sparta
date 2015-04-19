#ifndef H_MM
#define H_MM

#include "types.h"

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

void init_paging();

void change_page_directory(page_directory_t *newpd);

#endif