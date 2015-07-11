#include "apic.h"
#include "types.h"
#include "convert.h"
#include "video.h"
#include "memory.h"

uint32_t lapic_addr;

int32_t lapic_read(uint32_t lapic_reg_name)
{
  return *((volatile uint32_t *)lapic_addr);
}
uint32_t apicid()
{	
  //  P6 famili and Pentium processors
  // ----------------------------------
  // |    APIC ID |    Reserved       |
  // ----------------------------------
  // 31          24                   0
  return lapic_read(LAPIC_ID) >> 24;
}

void lapic_enable() 
{
  
}

inline int64_t rdmsr(uint32_t msr_id)
{
    int64_t msr_value;
    asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
    return msr_value;
}

inline void wrmsr(uint32_t msr_id, uint64_t msr_value)
{
    asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}

uint32_t get_apic_base()
{
  return ((uint32_t)rdmsr(IA32_APIC_BASE)) & 0xFFFFF000;
}

void msr_read(uint32_t reg, int32_t *msr_hi, int32_t *msr_lo)
{	
  long long value;
  asm volatile ( "rdmsr" : "=A" (value) : "c" (reg) );
  *msr_hi = value;
  *msr_lo = (int32_t)value;
}


void apic_info() 
{
  int64_t b = rdmsr(IA32_APIC_BASE);
  uint8_t buffer[64];
  memset(&buffer, '\0', 64);
  int_to_binary_string(b, &buffer);
  set_text_color(GREEN);
  write_text("\nAPIC base msr: ");write_text((string)&buffer);write_char('\n');
  uint8_t apic_global_enable = (b >> 11) & 0x1;
  set_text_color(GREEN);
  write_text("APIC global enable/disable: ");
  if (apic_global_enable) {
    write_text("enable");
  }
  else {
    write_text("disable");
  }
  write_text("\n");
  set_text_color(LIGTH_GRAY); 
}

void apic_init()
{
  apic_info();
  write_text("------------------------------------\n");
}
