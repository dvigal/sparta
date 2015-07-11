#include "paging.h"

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

page_t *get_page(virt_addr_t vaddr, page_directory_t *dir)
{
    uint32_t table_idx = TABLE_INDEX(vaddr);
    uint32_t page_idx = PAGE_INDEX(vaddr);
#ifdef DEBUG
    assert(table_idx >= 0, __LINE__, __FILE__);
    assert(page_idx >= 0, __LINE__, __FILE__);
#endif DEBUG
    
    if (dir->table[table_idx]) {
        return &dir->table[table_idx]->page[page_idx];
    } else {
        phys_addr_t page_table_addr = kmalloc_base(sizeof(page_table_t), true);
#ifdef DEBUG
    kprintf("Page Table Address: 0x%h\n", page_table_addr);
#endif
        dir->table[table_idx] = (page_table_t*) page_table_addr;
        dir->tbaddress[table_idx] = page_table_addr | PAGE_PRESENT_RW_USER;
        return &dir->table[table_idx]->page[page_idx];
    }
    return 0;
}

void pg_mapkernel(virt_addr_t *vaddr, phys_addr_t *paddr, page_directory_t *kernel_directory)
{
    while (*vaddr < get_kernel_end_addr()) {
        page_t *page = get_page(*vaddr, kernel_directory);
        page->present        = PAGE_PRESENT(true);
        page->rw             = PAGE_RW(true);
        page->user_superuser = PAGE_SUPERVISOR(false);
        page->baddress       = PAGE_PHYSICAL_BASE_ADDRESS(*paddr);

        *vaddr += PAGE_SIZE;
        *paddr += PAGE_SIZE;
    }
}

void load_page_directory(page_directory_t *pagedir)
{
#ifdef DEBUG
    kprintf("Base Address of Current Page Directory: 0x%h\n", &current_directory->tbaddress);
    kprintf("Base Address of New Page Directory: 0x%h\n", &pagedir->tbaddress);
#endif
  current_directory = pagedir;
  asm volatile("mov %0, %%cr3":: "r"(&pagedir->tbaddress));
  uint32_t cr0;
  asm volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0":: "r"(cr0));
#ifdef DEBUG
    kprintf("Base Address of New Page Directory has been loaded sucessfully!\n");
#endif
}

void init_paging()
{   
    kprintf("Virtual memory initialization start...\n");
    kprintf("Kernel physical address space: 0x%h - 0x%h, size: %d bytes\n", get_kernel_start_addr(), get_kernel_end_addr(), get_kernel_size());
    kernel_directory = (page_directory_t*) kmalloc_base(sizeof(page_directory_t), true);
    current_directory = kernel_directory;
  
#ifdef DEBUG
    kprintf("Base Address of the Kernel Page Directory: 0x%h\n", kernel_directory);
#endif
  
    virt_addr_t vaddr = 0;
    phys_addr_t paddr = 0;

    pg_mapkernel(&vaddr, &paddr, kernel_directory);

    load_page_directory(kernel_directory);
    
    kprintf("Virtual memory initialization done\n");
}

page_directory_t *get_current_page_directory()
{
    return current_directory;
}