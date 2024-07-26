#include "raylib.h"
#include "simulation.h"

void handle_input(Simulation *sim) {
  switch (GetKeyPressed()) {
  case KEY_UP:
    increase_tick(sim);
    break;
  case KEY_DOWN:
    decrease_tick(sim);
    break;
  case KEY_S:
    simulation_tick(sim);
    break;
  case KEY_K:
    simulation_kill(sim);
    break;
  case KEY_P:
    simulation_pause();
    break;
  default:
    // unimplemented
    break;
  }
}
