#include "mm.h"

page_directory_t *kernel_directory=0;


page_directory_t *current_directory=0;

uint32_t *frames;
uint32_t nframes;

uint32_t placement_address = 0x1000 + 0x1000000;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

static void set_frame(uint32_t frame_addr) {
  uint32_t frame = frame_addr/0x1000;
  uint32_t idx = INDEX_FROM_BIT(frame);
  uint32_t off = OFFSET_FROM_BIT(frame);
  frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr) {
  uint32_t frame = frame_addr/0x1000;
  uint32_t idx = INDEX_FROM_BIT(frame);
  uint32_t off = OFFSET_FROM_BIT(frame);
  frames[idx] &= ~(0x1 << off);
}

static uint32_t first_frame() {
  uint32_t i, j;
  for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
    if (frames[i] != 0xFFFFFFFF) {
      for (j = 0; j < 32; j++) {
	uint32_t toTest = 0x1 << j;
	if (!(frames[i]&toTest)) {
	  return i*4*8+j;
	}
      }
    }
  }
}

static uint32_t is_page_alignment(int align) {
  return align == 1 && (placement_address & 0xFFFFF000);
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
  if (page->frame != 0) {
    return;
  }
  uint32_t idx = first_frame();
  if (idx == (uint32_t)-1) {
    
  }
  set_frame(idx*0x1000);
  page->present = 1;
  page->rw = (is_writeable)?1:0;
  page->user = (is_kernel)?0:1;
  page->frame = idx;
}

void free_frame(page_t *page) {
  uint32_t frame;
  if (!(frame=page->frame)) {
    return;
  }
  clear_frame(frame);
  page->frame = 0x0;
}

uint32_t kmalloc(uint32_t size) {
  uint32_t tmp = placement_address;
  placement_address += size;
  return tmp;
}

uint32_t kmalloc_a(uint32_t size, int align) {
  if (align == 1 && (placement_address & 0xFFFFF000)) {
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  uint32_t tmp =  placement_address;
  placement_address += size;
  return tmp;
}

uint32_t kmalloc_ap(uint32_t size, int align, uint32_t *phys) {
  if (align == 1 && (placement_address & 0xFFFFF000)) {
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys) {
    *phys = placement_address;
  }
  uint32_t tmp = placement_address;
  placement_address += size;
  return tmp;
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
  address /= 0x1000;
  uint32_t table_idx = address / 1024;
  if (dir->tables[table_idx]) {
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else 
  if (make) {
    uint32_t tmp;
    dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), 1, &tmp);
    dir->tablesPhysical[table_idx] = tmp | 0x7;
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else {
    return 0;
  }
}

void init_paging() {
  uint32_t mem_end_page = 0x1000000;
  nframes = mem_end_page / 0x1000;
  frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
  kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t), 1);
  current_directory = kernel_directory;
  int i = 0;
  while (i < placement_address) {
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
    i += 0x1000;
  }
  change_page_directory(kernel_directory);
}

void change_page_directory(page_directory_t *newpd) {
  current_directory = newpd;
  asm volatile("mov %0, %%cr3":: "r"(&newpd->tablesPhysical));
  uint32_t cr0;
  asm volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0":: "r"(cr0));
}