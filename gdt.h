#ifndef H_GDT
#define H_GDT

struct gdt_struct {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
}__attribute__((packed));
typedef struct gdt_struct gdt_t;

struct gdt_r_struct {
  unsigned short limit;
  unsigned int base;
}__attribute__((packed));
typedef struct gdt_r_struct gdtr_t;

gdt_t gdt[3];
gdtr_t gdtr;

void init_gdt();

void set_gdt_gate(unsigned int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran);

void load_gdt(gdtr_t *ptr);

#endif