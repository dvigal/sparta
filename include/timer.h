#ifndef TIMER_H
#define TIMER_H

#include "types.h"
#include "system.h"

#define BASE_FREQUENCY_HZ 1193180

void init_timer(uint32_t hz);

#endif