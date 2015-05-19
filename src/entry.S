[global sge]
sge:
  int 66

[global read_cpuid]
read_cpuid:
  push ebp
  mov ebp, esp
  mov eax, [ebp + 8]
  cpuid
  push eax
  mov eax, [ebp + 12]
  mov [eax + 0xc], edx
  mov [eax + 0x8], ecx
  mov [eax + 0x4], ebx
  pop dword [eax]
  pop ebp
  ret

[global msr_write]
msr_write:
  push	ebp
  mov	ebp, esp
  mov	edx, [ebp + 12]
  mov	eax, [ebp + 16]
  mov	ecx, [ebp + 8]
  wrmsr
  pop	ebp
  ret

[global isr0]
isr0:
  cli
  push byte 0
  push byte 0
  jmp isr_common

[global isr3]
isr3:
  cli
  push byte 0
  push byte 3
  jmp isr_common  

[global isr8]
isr8:
  cli
  push byte 0
  push byte 8
  jmp isr_common

[global isr11]
isr11:
  cli
  push byte 0
  push byte 11
  jmp isr_common  

[global isr13]
isr13:
  cli
  push byte 0
  push byte 13
  jmp isr_common  
  
[global isr14]
isr14:
  cli
  push byte 0
  push byte 14
  jmp isr_common  

[global isr17]
isr17:
  cli
  push byte 0
  push byte 17
  jmp isr_common

[global isr66]
isr66:
  cli
  push byte 0
  push byte 66
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
