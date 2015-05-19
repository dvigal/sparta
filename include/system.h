#ifndef H_SYSTEM
#define H_SYSTEM

#include "types.h"

struct regs_struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax, vector, err_code, eip, cs, eflags, usersp, ss;
}__attribute__((packed));
typedef struct regs_struct regs_t;

extern void init_gdt();
extern void init_idt();
extern void init_isrs();
extern void init_irq();
extern void init_timer(unsigned int hz);

typedef void (*irq_handler_t) (regs_t *);

#define NULL(type) (type*)0

#endif