#include "port.h"

void port_out_b(unsigned short port, unsigned char data) {
  asm ("out %%al, %%dx"::"a"(data), "d"(port)); 
}