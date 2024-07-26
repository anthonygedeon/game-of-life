#include "scene.h"
#include "frame_buffer.h"

Scene scene_create() {
  FrameBuffer back_buffer = fb_create();
  FrameBuffer front_buffer = fb_create();

  return (Scene){
      .next = &back_buffer,
      .current = &front_buffer,
  };
}

void scene_draw(Scene *scene) {
  fb_clear(scene->next);

  fb_draw(scene->next, 0, 0);

  scene_swap(scene);
}

void scene_swap(Scene *scene) {
  FrameBuffer *temp = scene->current;
  scene->current = scene->next;
  scene->next = temp;
}

void scene_clear(Scene *scene) { fb_clear(scene->current); }
