#include "debug.h"
#include "video.h"
#include "convert.h"
#include "memory.h"

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
  
  static uint8_t buffer_size = 32;
  uint8_t buffer[32];
  
  memset(&buffer, '\0', buffer_size);
  int_to_dec_string(vector, &buffer);
  write_text("INTERRUPT VECTOR=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(err_code, &buffer);
  write_text("ERROR CODE=");write_text(&buffer);
  write_text("\n");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(eax, &buffer);
  write_text("EAX=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(ebx, &buffer);
  write_text("EBX=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(ecx, &buffer);
  write_text("ECX=");write_text(&buffer);
  write_text("\n");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(edx, &buffer);
  write_text("EDX=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(edi, &buffer);
  write_text("EDI=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(ebp, &buffer);
  write_text("EBP=");write_text(&buffer);
  write_text("\n");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(esp, &buffer);
  write_text("ESP=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(eip, &buffer);
  write_text("EIP=");write_text(&buffer);
  write_text("\n");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(eflags, &buffer);
  write_text("EFLAGS=");write_text(&buffer);
  write_text(" ");
  
  memset(&buffer, '\0', buffer_size);
  int_to_hex_string(usersp, &buffer);
  write_text("USER ESP=");write_text(&buffer);
  write_text("\n");
}