#include "convert.h"
#include "types.h"
#include "assert.h"

void string_reverse(char *begin, char *end) {
  char aux;
  while (end > begin) {
    aux = *end;
    *end-- = *begin;
    *begin++ = aux;
  }
}

void convert(int32_t value, char *str, uint8_t base) {
  static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        char *wstr = str;
        int sign;
        if (base < 2 || base > 35) {
                *wstr='\0';
                return;
        }
        if ((sign=value) < 0) {
                value = - value;
        }
        do {
                *wstr++=num[value%base];
        } while (value/=base);
        if (sign < 0) *wstr++='-';
        *wstr='\0';
        string_reverse(str, wstr-1);

}

void int_to_string(int32_t value, char *string) {
  convert(value, string, 10);
}