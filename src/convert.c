#include "convert.h"
#include "types.h"
#include "assert.h"
#include "memory.h"

const static uint8_t digits[] = {
        '0' , '1' , '2' , '3' , '4' , '5' ,
        '6' , '7' , '8' , '9' , 'a' , 'b' ,
        'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
        'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
        'o' , 'p' , 'q' , 'r' , 's' , 't' ,
        'u' , 'v' , 'w' , 'x' , 'y' , 'z'
    };

void string_reverse(uint8_t *begin, uint8_t *end) {
  uint8_t aux;
  while (end > begin) {
    aux = *end;
    *end-- = *begin;
    *begin++ = aux;
  }
}

static void int_to_string(int64_t value, uint8_t *buffer, uint8_t shift)
{
    uint8_t *tmp = buffer;
    uint8_t radix = 1 << shift;
    uint64_t mask = (uint64_t) (radix - 1);
    do {
      uint32_t index = value & mask;
      *tmp++ = digits[index];
      value = (uint64_t) (value >> shift);
    } while (value != 0);
    string_reverse(buffer, tmp-1);
}


void int_to_binary_string(int64_t value, uint8_t *buffer) 
{
    int_to_string(value, buffer, 1);  
}

void int_to_hex_string(int64_t value, uint8_t *buffer) 
{
    int_to_string(value, buffer, 4);  
}

void int_to_dec_string(int32_t value, uint8_t *buffer) 
{
  uint8_t *str = buffer;
  uint8_t base = 10;
  int32_t sign;
  if ((sign = value) < 0) {
    value = -value;
  }
  do {
    *str++ = digits[value % base];
  } while (value /= base);
  if (sign < 0) {
    *str++ = '-';
  }
  *str = '\0';
  string_reverse(buffer, str - 1);
}