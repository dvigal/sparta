#include "screen.h"
#include "paging.h"
#include "convert.h"
#include "apic.h"
#include "idt.h"
#include "gdt.h"
#include "isrs.h"
#include "memory.h"
#include "cpu_info.h"
#include "system.h"
#include "print.h"
#include "debug.h"
#include "mm.h"

void init_kernel() 
{
  init_gdt();
  kprintf("GDT...\n");
  init_idt();
  kprintf("IDT...\n");
  init_isrs();
  kprintf("ISRS...\n");
  init_irq();
  kprintf("IRQ...\n");
    
  apic_init();
  
  init_paging();
  
  init_mmanager();
}

void main()
{   
    clear();
    init_kernel();
    
    asm("sti");
//    vscreen_t *vscreen = init_vscreen();
//    
//    string brand = get_processor_brand();
//    kprintf("PROCESSOR BRAND: %s\n", brand);
//    
//    uint8_t stepping = get_stepping_id();
//    kprintf("STEPPING: %d\n", stepping);
//    
//    uint8_t model = get_model();
//    kprintf("MODEL: %d\n", model);
//    
//    uint8_t family = get_family_id();
//    kprintf("FAMILY: %d\n", family);
//    
//    uint8_t processor_type = get_processor_type();
//    kprintf("PROCESSOR TYPE: %d\n", processor_type);
//    
//    uint8_t msr_supported = is_msr_supported();
//    kprintf("MSR SUPPORTED: %s\n", msr_supported == 1 ? "true" : "false");
//
//    uint8_t apic_supported = is_apic_supported();
//    kprintf("APIC On-Chip: %d\n", apic_supported);
    
    
    // TODO: handle software exception...
//    assert(-1 > 0, __LINE__, __FILE__);
//    uint32_t *addr = (uint32_t*)34234234;
//    *addr = 4; // PAGE FAULT EXPECTED!
    for (;;);
}