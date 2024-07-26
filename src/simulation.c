#include "simulation.h"
#include "scene.h"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

Simulation simulation_create() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "Game of Life"
             " " VERSION);
  SetTargetFPS(60);

  Simulation sim;
  sim.simulation_is_running = true;
  sim.tick_speed = TICK_SPEED;
  sim.tick_rate = 1;
  sim.scene = scene_create();

  return sim;
}

bool simulation_status(Simulation *sim) {
  return sim->simulation_is_running || !WindowShouldClose();
}

void increase_tick(Simulation *sim) { sim->tick_speed += sim->tick_rate; }

void decrease_tick(Simulation *sim) { sim->tick_speed -= sim->tick_rate; }

void simulation_tick(Simulation *sim) {
  // update

  // clear

  // draw
}

void simulation_pause(void) {}

void simulation_restart(Simulation *sim) {
  sim->tick_speed = TICK_SPEED;
  sim->tick_rate = 1;
}

void simulation_run(Simulation *sim) {
  while (simulation_status(sim))
    simulation_tick(sim);
}

void simulation_kill(Simulation *sim) { scene_clear(&sim->scene); }

void simulation_seed(Simulation *sim) {
  // populate states of cells for each cell
}

void simulation_destroy() { CloseWindow(); }
