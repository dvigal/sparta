#ifndef IDT_H
#define IDT_H

#include "types.h"

struct idt_struct {
  uint16_t base_low;
  uint16_t selector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));
typedef struct idt_struct idt_t;

struct idt_r_struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));
typedef struct idt_r_struct idtr_t;

void init_idt(void);
void load_idtr(idtr_t *ptr);
void save_idtr(idtr_t *ptr);
void set_idt_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

#endif