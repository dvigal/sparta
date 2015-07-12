#ifndef IRQ_H
#define IRQ_H

#include "system.h"

#define IRQ_HANDLER_TABLE_SIZE 16

extern void irq0();

void init_irq();

void set_irq_handler(unsigned int num, void (*handler)(regs_t *reg));

void irq_handler(regs_t *reg);

#endif