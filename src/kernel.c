#include "screen.h"
#include "paging.h"
#include "convert.h"
#include "video.h"
#include "apic.h"
#include "idt.h"
#include "gdt.h"
#include "isrs.h"
#include "memory.h"
#include "cpu_info.h"
#include "system.h"

void init_kernel() 
{
  init_gdt();
  write_text("GDT\n");
  init_idt();
  write_text("IDT\n");
  init_isrs();
  write_text("ISRS\n");
  init_irq();
  write_text("IRQ\n");
  
  init_paging();
  apic_init();
}

void throw() {
    asm("int $66");
}

inline void assert(bool condition) {
    if (!condition) {
        throw();
    }
}

void main()
{   
    clear();
    char buffer[32];
    memset(&buffer, '\0', 32);
    int_to_dec_string(get_kernel_length() / 1024 / 1024, &buffer);
    write_text("KERNEL PHYS ADDRESS START: ");write_text(&buffer);write_text("\n");
   
    init_kernel();
    
    asm("sti");
    vscreen_t *vscreen = init_vscreen();
    
    
   
    string brand = get_processor_brand();
    write_text("PROCESSOR BRAND: ");write_text(brand);write_text("\n");
    
    uint8_t stepping = get_stepping_id();
    int_to_dec_string(stepping, &buffer);
    write_text("STEPPING: ");write_text(&buffer);write_text("\n");
    
    uint8_t model = get_model();
    memset(&buffer, '\0', 32);
    int_to_dec_string(model, &buffer);
    write_text("MODEL: ");write_text(&buffer);write_text("\n");
    
    uint8_t family = get_family_id();
    memset(&buffer, '\0', 32);
    int_to_dec_string(family, &buffer);
    write_text("FAMILY: ");write_text(&buffer);write_text("\n");
    
    uint8_t processor_type = get_processor_type();
    memset(&buffer, '\0', 32);
    int_to_dec_string(processor_type, &buffer);
    write_text("PROCESSOR TYPE: ");write_text(&buffer);write_text("\n");
    
    uint8_t msr_supported = is_msr_supported();
    memset(&buffer, '\0', 32);
    int_to_dec_string(msr_supported, &buffer);
    write_text("MSR SUPPORTED: ");write_text(&buffer);write_text("\n");

    uint8_t apic_supported = is_apic_supported();
    memset(&buffer, '\0', 32);
    int_to_dec_string(apic_supported, &buffer);
    write_text("APIC On-Chip: ");write_text(&buffer);write_text("\n");
    
    // TODO: handle software exception...
    //assert(-1 > 0);
    for (;;);
}