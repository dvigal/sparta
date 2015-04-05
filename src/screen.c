#include "screen.h"

void screen_clear_bw() {
  screen_clear(BLACK, WHITE);
}

void screen_clear(unsigned char backcolor, unsigned char forecolor) {
  int x,y;
  for (y = 0; y < ROWS; y++) {
      for (x = 0; x < COLS; x++) {
	  unsigned short* video = vga();
	  video += ((y * COLS) + x);
	  *video = (((backcolor << 4) | (forecolor & 0x0f)) << 8) | 0;
      }
  }
}