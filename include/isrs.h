#ifndef H_ISRS
#define H_ISRS

#include "system.h"

extern void isr0();
extern void isr3();
extern void isr8();
extern void isr11();
extern void isr13();
extern void isr14();
extern void isr17();

extern void isr66();

void init_isrs();

void exception_handler(regs_t *reg);

#endif