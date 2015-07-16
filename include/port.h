#ifndef PORT_H
#define PORT_H

#include "types.h"

static void port_out_b(uint16_t port, uint8_t data) {
  asm ("out %%al, %%dx"::"a"(data), "d"(port)); 
}

#endif