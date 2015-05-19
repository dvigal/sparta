#ifndef H_APIC
#define H_APIC

#include "types.h"

#define IA32_APIC_BASE	0x1b

extern uint32_t lapic_addr;
extern msr_write(uint32_t msr, uint32_t h, uint32_t l);

#define LAPIC_DEF_ADDR	0x0FEE00000

#define LAPIC_ID	(lapic_addr + 0x020)
#define LAPIC_VERSION 	(lapic_addr + 0x030)
#define LAPIC_TPR	(lapic_addr + 0x080)
#define LAPIC_PPR	(lapic_addr + 0x0A0)

int32_t lapic_read(uint32_t lapic_reg_name);

uint32_t apicid();

void apic_init();

#endif