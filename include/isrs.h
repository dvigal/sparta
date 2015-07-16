#ifndef ISRS_H
#define ISRS_H

#include "system.h"

extern void isr0(void);
extern void isr3(void);
extern void isr8(void);
extern void isr11(void);
extern void isr13(void);
extern void isr14(void);
extern void isr17(void);

extern void isr66(void);

void init_isrs(void);

void exception_handler(regs_t *reg);

#endif