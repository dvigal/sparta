#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "screen.h"
#include "port.h"

const char *exception_messages[] = {
  "Divide Error",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

void init_isrs() {
  set_idt_gate(0, (unsigned int)isr0, 0x08, 0x8E);
  
  set_idt_gate(32, (unsigned int)irq0, 0x08, 0x8E);
}

void exception_handler(regs_t *reg) {
  if (reg->vector < 32) {
    screen_clear_bw();
    char * message = exception_messages[reg->vector];
    int x = 5;
    while(*message != 0) {
	  unsigned short* video = 0xB8000;
	  video += ((0 * COLS) + x);
	  *video = (((BLACK << 4) | (WHITE & 0x0f)) << 8) | *message;
	  message++;
	  x++;
    }
    //asm("cli\n"
//	"hlt");
  }
}