#include "screen.h"

unsigned short* vga() {
  return (unsigned short*) VIDEO_ADDRESS;
}


void init_kernel() {
  init_gdt();
  init_idt();
  init_isrs();
  init_irq();
}


void main()
{   
    screen_clear_bw();
   
    char* messageWelcome = "Congratulation!";
    int x = 5;
    while(*messageWelcome != 0) {
      unsigned short* video = vga();
      video += ((0 * COLS) + x);
      *video = (((BLACK << 4) | (WHITE & 0x0f)) << 8) | *messageWelcome;
      messageWelcome++;
      x++;
    }
    init_kernel();
    asm("sti");
    for (;;);
}