#include "idt.h"

idt_t idt[256];
idtr_t idtr;

void init_idt() {
  idtr.limit = (sizeof(idt_t) * 256) - 1;
  idtr.base = (unsigned int) &idt;
  
  load_idtr(&idtr);
}

void load_idtr(idtr_t *ptr) {
    asm volatile ("lidt %0"::"m"(*ptr));
}

void save_idtr(idtr_t *ptr) {
    // not yet implemented
}

void set_idt_gate(unsigned char num, unsigned int base, unsigned short selector, unsigned char flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].reserved = 0;
    idt[num].flags = flags;
}