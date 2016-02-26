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

extern phys_addr_t kernel_phys_address_start;
extern phys_addr_t kernel_phys_address_end;

//phys_addr_t placement_address = 0x1000 + 0x1000000;
#define KERNEL_START        ((phys_addr_t) &kernel_phys_address_start)
#define KERNEL_END          ((phys_addr_t) &kernel_phys_address_end)
#define KERNEL_SIZE         (KERNEL_END - KERNEL_START)
#define KERNEL_HEAP_START   (KERNEL_END)

kinfo_t kinfo;

void pre_init(void)
{
    kinfo.kernel_start = KERNEL_START;
    kinfo.kernel_end   = KERNEL_END;
    kinfo.kernel_len   = KERNEL_SIZE;
}

void main(void)
{       
    pre_init();
        
    clear();
    kprintf("    _____                  _        \n");
    kprintf("   /  ___|                | |       \n");
    kprintf("   \\ `--. _ __   __ _ _ __| |_ __ _ \n");
    kprintf("    `--. \\ '_ \\ / _` | '__| __/ _` |\n");
    kprintf("   /\\__/ / |_) | (_| | |  | || (_| |\n");
    kprintf("   \\____/| .__/ \\__,_|_|   \\__\\__,_|\n");
    kprintf("         | |\n");
    kprintf("         |_|\n\n\n");
    
    init_gdt();
    kprintf("GDT...\n");
    init_idt();
    kprintf("IDT...\n");
    init_isrs();
    kprintf("ISRS...\n");
    init_irq();
    kprintf("IRQ...\n");
    apic_init();

    init_paging(&kinfo);
    init_mmanager(&kinfo);
    
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
