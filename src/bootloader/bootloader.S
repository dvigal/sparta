[org 0x7c00]
[bits 16]

KERNEL_OFFSET equ 0x1000
KERNEL_SECTOR_COUNT equ 32
FLOPPY_DEVICE equ 0x0

start:
  cli
  xor ax, ax
  mov ds, ax,
  mov es, ax
  mov ax, 0x90000
  mov ss, ax
  mov sp, 0xFFFF
  sti
  ;;mov bx, bootstring
  ;;call print
load_kernel:  
  mov bx, KERNEL_OFFSET
  mov ch, 0x00
  mov cl, 0x02
  mov dh, 0x00
  mov ah, 0x02
  mov al, KERNEL_SECTOR_COUNT
  mov dl, FLOPPY_DEVICE
  int 0x13
  cmp ax, KERNEL_SECTOR_COUNT
  je loaded
  
  jc load_error  
  pop dx         
  cmp al, dh                     
  jne load_error  
  hlt
loaded:
  cli
  lgdt [gdt_desc]
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax
  jmp 0x08:start_protected

[bits 32]
start_protected:
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  mov esp, 0x7000
  jmp KERNEL_OFFSET
  
print:
    mov ah, 0xE 
    mov al, [bx]
    cmp al, 0    
    jz print_done
    int 0x10     
    inc bx       
    jmp print    
print_done:
    ret
load_error:
    mov bx, load_err_msg
    call print
    jmp $
    
gdt:                
gdt_null: 
    dd 0  
    dd 0  
gdt_cs:
    dw 0xffff
    dw 0     
    db 0     
    db 10011010b
                
    db 11001111b
    db 0        
gdt_ds:
    dw 0xffff   
    dw 0        
    db 0        
    db 10010010b
                
    db 11001111b
    db 0        
gdt_end:        

gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt

CODE_SEG equ gdt_cs - gdt
DATA_SEG equ gdt_ds - gdt

bootstring:   db "Loading...", 0
load_err_msg: db "Cannot load from disk", 0

times 510 -( $ - $$ ) db 0  
dw 0xAA55 