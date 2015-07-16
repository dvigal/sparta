#include "gdt.h"

void init_gdt(void) {
  gdtr.limit = (sizeof(gdt_t) * 3) - 1;
  gdtr.base  = (uint32_t)&gdt;

  set_gdt_gate(0, 0, 0, 0, 0);           
  set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  
  load_gdt(&gdtr);
}

void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
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