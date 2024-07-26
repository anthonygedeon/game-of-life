#include "frame_buffer.h"
#include "utils.h"

void fb_clear(FrameBuffer *fb) {
  for (int i = 0; i < WORLD_HEIGHT; i++) {
    for (int j = 0; j < WORLD_WIDTH; j++) {
      fb->pixels[i][j] = 0;
    }
  }
}

FrameBuffer fb_create() { return (FrameBuffer){.pixels = {}}; }

void fb_draw(FrameBuffer *fb, int x, int y) { fb->pixels[y][x] = 1; }
