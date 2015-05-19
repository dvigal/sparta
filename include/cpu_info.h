#ifndef H_CPU_INFO
#define H_CPU_INFO

#include "types.h"

static const string *processor_brand_table[] = {
  "This processor does not support the brand identification feature",
  "Intel(R) Celeron(R) processor",
  "Intel(R) Pentium(R) III processor",
  "Intel(R) Pentium(R) III XeonTM processor",
  "Intel(R) Pentium(R) III processor",
  "Mobile Intel(R) Pentium(R) III processor-M",
  "Mobile Intel(R) Celeron(R) processor",
  "Intel(R) Pentium(R) 4 processor",
  "Intel(R) Pentium(R) 4 processor",
  "Intel(R) Celeron(R) processor",
  "Intel(R) Xeon(TM) processor",
  "Intel(R) Xeon(TM) processor MP",
  "Mobile Intel(R) Pentium(R) 4 processor-M",
  "Mobile Intel(R) Celeron(R) processor",
  "Mobile Genuine Intel(R) processor",
  "Intel(R) Celeron(R) M processor",
  "Mobile Intel(R) Celeron(R) processor",
  "Intel(R) Celeron(R) processor",
  "Mobile Genuine Intel(R) processor",
  "Intel(R) Pentium(R) M processor",
  "Mobile Intel(R) Celeron(R) processor",
  "RESERVED"
};

struct cpu_info_struct {
  uint32_t eax,ebx,ecx,edx;
}__attribute__((packed));
typedef struct cpu_info_struct cpu_info_t;

extern void read_cpuid(uint32_t mode, cpu_info_t *cpu_info); 

static string *get_processor_brand()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  uint8_t index = cpu_info.ebx & 0xF;
  if (index > 21) {
    return (string)0;
  }  
  return processor_brand_table[index];
}

static uint8_t get_stepping_id()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return cpu_info.eax & 0xF;
}

static uint8_t get_model()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.eax >> 4) & 0xF;
}

static uint8_t get_family_id()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.eax >> 8) & 0xF;
}

static uint8_t get_processor_type()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.eax >> 12) & 0x3;
}

static uint8_t get_ext_model_id()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.eax >> 16) & 0xF;
}

static uint8_t get_ext_family_id() 
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.eax >> 20) & 0xFF;
}

static uint8_t is_msr_supported()
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.edx >> 5) & 0x1;
}

static uint8_t is_apic_supported() 
{
  cpu_info_t cpu_info;
  read_cpuid(1, &cpu_info);
  return (cpu_info.edx >> 9) & 0x1;
}

#endif