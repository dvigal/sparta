#include "debug.h"
#include "print.h"

void pretty_print_reg(regs_t * reg) 
{
  int32_t vector = reg->vector;
  int32_t err_code = reg->err_code;
  int32_t eax = reg->eax;
  int32_t ebx = reg->ebx;
  int32_t ecx = reg->ecx;
  int32_t edx = reg->edx;
  int32_t edi = reg->edi;
  
  int32_t ebp = reg->ebp;
  int32_t esp = reg->esp;
  int32_t eip = reg->eip;
  
  int32_t eflags = reg->eflags;
  int32_t usersp = reg->usersp;
  
  kprintf("INTERRUPT VECTOR=%d ", vector);
  kprintf("ERROR CODE=%d\n", err_code);
  kprintf("EAX=%x ", eax);
  kprintf("EBX=%x ", ebx);
  kprintf("ECX=%x\n", ecx);
  kprintf("EDX=%x ", edx);
  kprintf("EDI=%x ", edi);
  kprintf("EBP=%x\n", ebp);
  kprintf("ESP=%x ", esp);
  kprintf("EIP=%x\n", eip);
  kprintf("EFLAGS=%x ", eflags);
  kprintf("USER ESP=%x\n", usersp);
}

void throw() {
    asm("int $66");
}

void assert(bool condition, uint32_t line_number, string filename) {
    if (!condition) {
        kprintf("File %s, Line %d\n", filename, line_number);
        throw();
    }
}