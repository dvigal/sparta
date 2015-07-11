#include "video.h"
#include "port.h"
#include "system.h"

/*
16 bit

15 14 13 12 | 11 10 9 8 | 7 6 5 4 3 2 1 0
------------ ----------- -----------------
back color    char color  char
*/

static const uint16_t *video_memory = (uint16_t*) VIDEO_MEMORY;
static const uint8_t width = WIDTH;
static const uint8_t height = HEIGHT;
static uint8_t current_x = 0;
static uint8_t current_y = 0;
static uint8_t background_color = BLACK;
static uint8_t text_color = LIGTH_GRAY;

void write_char(uint8_t c) 
{
  if (c == BACKSPACE_SYMBOL && current_x > 0) {
    current_x--;
    return;
  }
  if (c == RETURN_SYMBOL) {
    current_x = 0;
    return;
  }
  if (c == NEW_LINE_SYMBOL) {
    current_x = 0;
    current_y++;
    return;
  }
  uint16_t *location = video_memory + (current_y * width + current_x);
  *location = (((background_color << 4) | (0xFF & text_color)) << 8) | (0xFFFF & c);
  current_x++;
}

void write_text2a(string text, uint32_t length)
{
  uint32_t i = 0;
  while ((i < length || length == -1) && text[i]) {
    write_char(text[i++]);
  }
}

void write_text(string text)
{
    write_text2a(text, -1);
}

void clear() 
{
  uint16_t blank = ' ' | ((BLACK << 4)| (WHITE & 0xF) << 8);
  uint16_t *location = video_memory;
  int i;
  for (i = 0; i < width * height; i++) { 
    location[i] = blank;
  }
  move_cursor(0, 0);
}

uint8_t get_background_color()
{
  return background_color;
}

void set_background_color(uint8_t color)
{
  background_color = color;
}

uint8_t get_text_color()
{
  return text_color;
}

void set_text_color(uint8_t color)
{
  text_color = color;
}

void move_cursor(uint8_t x, uint8_t y)
{
  if (x < 0 || y < 0 || x > width || y > height) {
    return;
  }
  current_x = x;
  current_y = y;
  uint16_t position = width * y + x;
  port_out_b(0x3D4, 0x0E);
  port_out_b(0x3D5, position >> 8);
  port_out_b(0x3D4, 0x0F);
  port_out_b(0x3D5, position);
}

void move_cursor_left()
{
  move_cursor(current_x - 1, current_y);
}

void move_cursor_right()
{
  move_cursor(current_x + 1, current_y);
}

void move_cursor_up()
{
  move_cursor(current_x, current_y - 1);
}

void move_cursor_down()
{
  move_cursor(current_x, current_y + 1);
}