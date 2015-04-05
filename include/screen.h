#ifndef H_SCREEN
#define H_SCREEN

#define ROWS 25
#define COLS 80
#define WHITE 0xff
#define BLACK 0x00
#define VIDEO_ADDRESS 0xb8000

void screen_clear_bw();

void screen_clear(unsigned char backcolor, unsigned char forecolor);

#endif