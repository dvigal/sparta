ENTRY(start)
    
    _kernel_phys_address_start = 4M; 
    _kernel_vir_address_start = _kernel_phys_address_start;
    _kernel_phys_address_end = 40M;
    _kernel_length = _kernel_phys_address_end - _kernel_phys_address_start;

SECTIONS
{   . = _kernel_phys_address_start;
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
