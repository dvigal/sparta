#include "timer.h"
#include "port.h"
#include "irq.h"
#include "screen.h"

static unsigned long ticks = 0;
static long row = 1;
static void timer(regs_t *reg) {
  screen_clear_bw();
  ticks++;
  
  char* message = "Tick!";
  int x = 5;
  while(*message != 0) {
    unsigned short* video = (unsigned short*) 0xb8000;
    video += ((row * COLS) + x);
    *video = (((BLACK << 4) | (WHITE & 0x0f)) << 8) | *message;
    message++;
    x++;
  }
  if (row >= 25) {
    row = 0;
  } else {
    row++;
  }
}

void init_timer(unsigned int hz) {
    
    unsigned int divisor = 1193180 / hz;
    
    port_out_b(0x43, 0x36);
    port_out_b(0x40, (unsigned char)(divisor & 0xFF));
    port_out_b(0x40, (unsigned char)((divisor >> 8) & 0xFF));
    
    set_irq_handler(0, timer);
}