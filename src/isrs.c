#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "port.h"
#include "video.h"
#include "debug.h"

const char *exception_messages[] = {
  "\nDividing by Zero Error Encoutered!    \n",
  "Not Implemented",
  "Not Implemented",
  "Not Implemented",
  "Overflow",
  "Bound Range Exceeded",
  "Invalid Opcode",
  "Not Implemented",
  "Double Fault",
  "Not Implemented",
  "Not Implemented",
  "Segment Not Present",
  "Stack-Segment Fault",
  "General Protection",
  "Page Fault!",
  "Not Implemented",
  "Not Implemented",
  "Aligment Check",
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

const char *software_general_exception_message[] = {
    "SOFTWARE-GENERAL EXCEPTION"
};

void init_isrs() {
  set_idt_gate(0,  (uint32_t)  isr0, 0x08, 0x8E);
  set_idt_gate(3,  (uint32_t)  isr3, 0x08, 0x8E);
  set_idt_gate(8,  (uint32_t)  isr8, 0x08, 0x8E);
  set_idt_gate(11, (uint32_t)  isr11, 0x08, 0x8E);
  set_idt_gate(13, (uint32_t)  isr13, 0x08, 0x8E);
  set_idt_gate(14, (uint32_t)  isr14, 0x08, 0x8E);
  set_idt_gate(17, (uint32_t)  isr17, 0x08, 0x8E);
  set_idt_gate(32, (uint32_t)  irq0, 0x08, 0x8E);
  set_idt_gate(66, (uint32_t)  isr66, 0x08, 0x8E);
}

void exception_handler(regs_t *reg) {
  if (reg->vector < 32) {
    uint8_t color = get_text_color();
    set_text_color(RED);
    write_text(exception_messages[reg->vector]);
    write_text("\n");
    pretty_print_reg(reg);
    set_text_color(color);
    asm("cli\nhlt");
  }
  if (reg->vector == 66) {
    uint8_t color = get_text_color();
    set_text_color(RED);
    write_text(software_general_exception_message[0]);
    write_text("\n");
    pretty_print_reg(reg);
    set_text_color(color);
  }
}