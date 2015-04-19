#include "screen.h"
#include "system.h"
#include "types.h"

#define VSCREEN_SIZE	4

static vscreen_t vscreens[VSCREEN_SIZE];
static uint32_t vscreens_size = 0;
static uint8_t current_vscreen_idx;
static vscreen_t *current_vscreen;

vscreen_t *get_current_vscreen()
{
  return current_vscreen;
}

vscreen_t *create_vscreen()
{
}

vscreen_t *set_current_vscreen(vscreen_t *vscreen)
{
  current_vscreen = vscreen;
  uint8_t i = 0;
  while (i < VSCREEN_SIZE) {
    if (current_vscreen != &vscreens[i]) {
      vscreens[i++].active = false;
    } else
    {
      vscreens[i++].active = true;
    }
  }
  return current_vscreen;
}

vscreen_t *init_vscreen()
{	
    int i = 0;
    for (; i < VSCREEN_SIZE; i++ ) {
      vscreen_t vscreen = vscreens[i];
      vscreen.active = false;
      vscreen.background_color = BLACK;
      vscreen.text_color = LIGTH_GRAY;
      set_current_vscreen(&vscreen);
      
    }
    vscreens[0].active = true;
    return &vscreens[0];
}

vscreen_t *next_vscreen() 
{
  if (current_vscreen_idx == VSCREEN_SIZE - 1) {
    return &vscreens[0];
  }
  return &vscreens[current_vscreen_idx + 1];
}

vscreen_t *previous_vscreen() 
{
    if (current_vscreen_idx == 0) {
      return &vscreens[VSCREEN_SIZE - 1];
    }
    return &vscreens[current_vscreen_idx-1];
}

void print_text(vscreen_t *vscreen, string text) 
{
  uint32_t start = vscreen->cursor;
  uint32_t current = start;
  uint32_t i = 0;
  while (text[i]) {
    vscreen->buffer[current] = text[i++];
    current++;
  }
  vscreen->cursor = current;
  for (; start <= current; start++) {
    write_char(vscreen->buffer[start]);
  }
}

void clear_vscreen(vscreen_t *vscreen) 
{
  clear();
  uint32_t i = 0;
  while (vscreen->buffer[i]) {
    vscreen->buffer[i++] = ' ';
  }
}

void load_vscreen(vscreen_t* vscreen)
{
  clear();
  write_text(&(vscreen->buffer));
}