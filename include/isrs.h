#ifndef H_ISRS
#define H_ISRS

#include "system.h"

extern void isr0();

extern void isr14();

void init_isrs();
void exception_handler(regs_t *reg);

#endif