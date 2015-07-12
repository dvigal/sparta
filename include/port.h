#ifndef PORT_H
#define PORT_H


static void port_out_b(unsigned short port, unsigned char data) {
  asm ("out %%al, %%dx"::"a"(data), "d"(port)); 
}

#endif