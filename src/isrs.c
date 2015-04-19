#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "port.h"
#include "video.h"

const char *exception_messages[] = {
  "\nDividing by Zero Error Encoutered!    \n",
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
  "Page Fault!",
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
  set_idt_gate(14, (unsigned int)isr14, 0x08, 0x8E);
  set_idt_gate(32, (unsigned int)irq0, 0x08, 0x8E);
}

void exception_handler(regs_t *reg) {
  if (reg->vector < 32) {
    set_text_color(RED);
    write_text(exception_messages[reg->vector]);
    asm("cli\nhlt");
  }
}