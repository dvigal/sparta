#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

#define VIDEO_MEMORY		0xB8000

#define BLACK			0x0
#define BLUE 			0x1
#define GREEN			0x2
#define CIAN			0x3
#define RED			0x4
#define MAGENTA			0x5
#define BROWN			0x6
#define LIGTH_GRAY		0x7
#define DARK_GRAY		0x8
#define LIGTH_BLUE		0x9
#define LIGTH_GREEN		0xA
#define LIGTH_CIAN		0xB
#define LIGTH_RED		0xC
#define LIGTH_MAGENTA		0xD
#define LIGTH_BROWN		0xE
#define WHITE			0xF

#define DEFAULT                 BLACK

#define WIDTH			80
#define HEIGHT			25

#define NEW_LINE_SYMBOL		'\n'
#define RETURN_SYMBOL		'\r'
#define BACKSPACE_SYMBOL	0x08
  
void write_char(uint8_t c);

void write_text2(string text, uint32_t length);

void write_text(string text);

void clear();

uint8_t get_background_color();

void set_background_color(uint8_t color);

uint8_t get_text_color();

void set_text_color(uint8_t color);

void move_cursor(uint8_t x, uint8_t y);

void move_cursor_left();

void move_cursor_right();

void move_cursor_up();

void move_cursor_down();

#endif