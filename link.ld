ENTRY(start)
    
    kernel_phys_address_start = 4M;
    kernel_phys_address_end   = end;
SECTIONS
{   . = kernel_phys_address_start;
    .text ALIGN(4K) :
    {
        code = .; _code = .; __code = .;
        *(.text)
    }

    .data ALIGN(4K) :
    {
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
    }

    .bss ALIGN(4K) :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
    }
    end = .; _end = .; __end = .;
}
