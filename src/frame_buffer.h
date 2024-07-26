#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "utils.h"
#include <stdint.h>

typedef struct {
  uint8_t pixels[WORLD_HEIGHT][WORLD_WIDTH];
} FrameBuffer;

FrameBuffer fb_create();
void fb_clear(FrameBuffer *fb);
void fb_draw(FrameBuffer *fb, int x, int y);

#endif
