#include "irq.h"
#include "idt.h"
#include "memory.h"
#include "timer.h"
#include "screen.h"

static irq_handler_t irq_handlers[IRQ_HANDLER_TABLE_SIZE] = {0,0,0,0,
					      0,0,0,0,
					      0,0,0,0,
					      0,0,0,0};

void init_pic() {
  port_out_b(0x20, 0x11);
  port_out_b(0xA0, 0x11);

  port_out_b(0x21, 0x20);
  port_out_b(0xA1, 0x28);

  port_out_b(0x21, 0x04);
  port_out_b(0xA1, 0x02);

  port_out_b(0x21, 0x01);
  port_out_b(0xA1, 0x01);

  port_out_b(0x21, 0x0);
  port_out_b(0xA1, 0x0);
}

void init_irq() {
    
    init_pic();
    init_timer(20);
}

void set_irq_handler(unsigned int num, irq_handler_t handler) {
  irq_handlers[num] = handler;
}

void irq_handler(regs_t *reg) {
  /*
  if (reg->vector > 48 || reg->vector < 32) {
    char* messageWelcome = "Oops!";
    int x = 5;
    while(*messageWelcome != 0) {
	  unsigned short* video = (unsigned short*) VIDEO_ADDRESS;
	  video += ((0 * COLS) + x);
	  *video = (((BLACK << 4) | (WHITE & 0x0f)) << 8) | *messageWelcome;
	  messageWelcome++;
	  x++;
    }
  }
  */
  int num = reg->vector - 32;
  if (num >= 0 && num < IRQ_HANDLER_TABLE_SIZE) {  
    irq_handler_t handler = irq_handlers[num];
    if (handler != 0) {  
      handler(&reg);
    }
  }
  port_out_b(0x20, 0x20);
}