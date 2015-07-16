#ifndef GDT_H
#define GDT_H

#include "types.h"

struct gdt_struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
}__attribute__((packed));
typedef struct gdt_struct gdt_t;

struct gdt_r_struct {
  uint16_t limit;
  uint32_t base;
}__attribute__((packed));
typedef struct gdt_r_struct gdtr_t;

gdt_t gdt[3];
gdtr_t gdtr;

void init_gdt(void);

void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void load_gdt(gdtr_t *ptr);

#endif