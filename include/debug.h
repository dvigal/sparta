#ifndef H_DEBUG
#define H_DEBUG
#include "system.h"

void pretty_print_reg(regs_t * reg);

void throw();

void assert(bool condition, uint32_t line_number, string filename);

#endif