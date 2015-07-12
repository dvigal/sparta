#ifndef CONVERT_H
#define CONVERT_H

#include "types.h"

void convert(int32_t value, uint8_t *string, uint8_t base);

void int_to_binary_string(int64_t value, uint8_t *buffer);

void int_to_hex_string(int64_t value, uint8_t *buffer);

void int_to_dec_string(int32_t value, uint8_t *buffer);

#endif