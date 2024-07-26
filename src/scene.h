#ifndef SCENE_H
#define SCENE_H

#include "frame_buffer.h"

typedef struct {
  FrameBuffer *next;
  FrameBuffer *current;
} Scene;

Scene scene_create();
void scene_draw(Scene *scene);
void scene_swap(Scene *scene);
void scene_clear(Scene *scene);

#endif
