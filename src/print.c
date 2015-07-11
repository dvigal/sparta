#include "print.h"
#include "types.h"
#include "video.h"
#include "memory.h"

void kprintf(string fmt, ...)
{   
    va_list args;
    
    const uint32_t buffer[256];
    
    va_start(args, fmt);
    while (*fmt) {
        uint8_t symbol = (uint8_t) *fmt++;
        if (symbol != '%') {
            write_char(symbol);
            continue;
        }
        memset(&buffer, '\0', 256);
        symbol = (uint8_t) *fmt++;
        switch (symbol) {
            case '%':
                write_char(symbol);
                break;
            case 's':
                write_text(va_arg(args, uint8_t *));
                break;
            case 'd':
                int_to_dec_string(va_arg(args, int32_t), &buffer);
                write_text(&buffer);
                break;
            case 'h':
                int_to_hex_string((int64_t) va_arg(args, int32_t), &buffer);
                write_text(&buffer);
                break;
            case 'b':
                int_to_binary_string((int64_t) va_arg(args, int32_t), &buffer);
                write_text(&buffer);
                break;
            default:
                break;
        }
    }
    va_end(args);
}