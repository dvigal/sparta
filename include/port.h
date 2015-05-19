#ifndef H_PORT
#define H_PORT


static void port_out_b(unsigned short port, unsigned char data) {
  asm ("out %%al, %%dx"::"a"(data), "d"(port)); 
}

#endif