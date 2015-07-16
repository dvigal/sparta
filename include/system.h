#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

struct regs_struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax, vector, err_code, eip, cs, eflags, usersp, ss;
}__attribute__((packed));
typedef struct regs_struct regs_t;

struct kernel_info {
    phys_addr_t kernel_start;
    phys_addr_t kernel_end;
    phys_addr_t kernel_len;
    phys_addr_t kernel_pde_addr;
};
typedef struct kernel_info kinfo_t;

extern void init_gdt(void);
extern void init_idt(void);
extern void init_isrs(void);
extern void init_irq(void);
extern void init_timer(uint32_t hz);

typedef void (*irq_handler_t) (regs_t *);


#define UINT32_T_MAX_VALUE  0x7fffffff

#endif