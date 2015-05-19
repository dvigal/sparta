#ifndef H_SCREEN
#define H_SCREEN

#include "video.h"
#include "types.h"

struct vscreen {
  uint32_t x;
  uint32_t y;
  uint8_t buffer[WIDTH * HEIGHT];
  uint16_t cursor;
  uint8_t background_color;
  uint8_t text_color;
  bool active;
};
typedef struct vscreen vscreen_t;

vscreen_t *get_current_vscreen();

vscreen_t *init_vscreen();

vscreen_t *create_vscreen();

vscreen_t *set_current_vscreen(vscreen_t *current_vscreen);

vscreen_t *next_vscreen();

vscreen_t *previous_vscreen();

void print_text(vscreen_t *vscreen, string text);

void clear_vscreen(vscreen_t *vscreen);

void load_vscreen(vscreen_t *vscreen);

#endif