#ifndef H_ISRS
#define H_ISRS

#include "system.h"

extern void isr0();

void init_isrs();
void exception_handler(regs_t *reg);

#endif