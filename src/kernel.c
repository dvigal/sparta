#include "screen.h"
#include "mm.h"
#include "convert.h"
#include "video.h"

void init_kernel() 
{
  init_gdt();
  init_idt();
  init_isrs();
  init_irq();
  init_paging();
}


void main()
{   
    clear();
    init_kernel();
    vscreen_t *vscreen = init_vscreen();
    asm("sti");
    for (;;);
}