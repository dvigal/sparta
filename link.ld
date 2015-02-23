ENTRY (kernel_entry)

SECTIONS
{
  . = 1M;
  
  kernel_start = .;
  
  .text : {
    *(.text)
  }
  
  .data ALIGN(4096) : {
    *(.data)
  }
  
  .rodata ALIGN(4096) : {
    *(.rodata)
  }
  
  .bss ALIGN(4096) : {
    *(.bss)
  }
  
  . = ALIGN(4096);
  kernel_end = .;
}