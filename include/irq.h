#ifndef H_IRQ
#define H_IRQ

#include "system.h"

#define IRQ_HANDLER_TABLE_SIZE 16

extern void irq0();

void init_irq();

void set_irq_handler(unsigned int num, void (*handler)(regs_t *reg));

void irq_handler(regs_t *reg);

#endif