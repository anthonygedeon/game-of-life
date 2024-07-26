#ifndef SIMULATION_H
#define SIMULATION_H

#include "scene.h"
#include <stdbool.h>

typedef struct {
  int tick_rate;
  int tick_speed; // tick_speed controls the speed of the simulation. Lower =
                  // faster, Higher = slower

  bool simulation_is_running;

  Scene scene;
} Simulation;

Simulation simulation_create();
bool simulation_status(Simulation *sim);

void increase_tick(Simulation *sim);

void decrease_tick(Simulation *sim);

void simulation_tick(Simulation *sim);
void simulation_pause(void);

void simulation_restart(Simulation *sim);

void simulation_run(Simulation *sim);

void simulation_kill(Simulation *sim);

void simulation_seed(Simulation *sim);

void simulation_destroy();

#endif
