#ifndef IRQ_H
#define IRQ_H

#include "types.h"
#include "system.h"

#define IRQ_HANDLER_TABLE_SIZE 16

extern void irq0(void);

void init_irq(void);

void set_irq_handler(uint32_t num, void (*handler)(regs_t *reg));

void irq_handler(regs_t *reg);

#endif