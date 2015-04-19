[bits 32]
[extern main]
jmp main
cli
hlt

[global isr0]
isr0:
  cli
  push byte 0
  push byte 0
  jmp isr_common
  
[global isr14]
isr14:
  cli
  push byte 0
  push byte 0
  jmp isr_common  
  
[global irq0]
irq0:
  cli
  push byte 0
  push byte 32
  jmp irq_common
  
[extern exception_handler]
isr_common:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov eax, esp
  push eax
  mov eax, exception_handler
  call eax
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8
  sti
  iret
  
[extern irq_handler]
irq_common:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov eax, esp
  push eax
  mov eax, irq_handler
  call eax
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8
  iret