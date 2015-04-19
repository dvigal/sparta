#include "timer.h"
#include "port.h"
#include "irq.h"
#include "screen.h"

static uint64_t ticks = 0;

static void timer(regs_t *reg)
{
  ticks++;
}

void init_timer(unsigned int hz)
{
    uint32_t divisor = 1193180 / hz;
    
    port_out_b(0x43, 0x36);
    port_out_b(0x40, (uint8_t)(divisor & 0xFF));
    port_out_b(0x40, (uint8_t)((divisor >> 8) & 0xFF));
    
    set_irq_handler(0, timer);
}