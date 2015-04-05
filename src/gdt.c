#include "gdt.h"

void init_gdt() {
  gdtr.limit = (sizeof(gdt_t) * 3) - 1;
  gdtr.base  = (unsigned int)&gdt;

  set_gdt_gate(0, 0, 0, 0, 0);           
  set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  
  load_gdt(&gdtr);
}

void set_gdt_gate(unsigned int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = (limit >> 16) & 0x0F;

  gdt[num].granularity |= gran & 0xF0;
  gdt[num].access = access;
}

void load_gdt(gdtr_t *ptr) {
  asm volatile ("lgdt %0"::"m"(*ptr));
}