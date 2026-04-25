#include "init.h"
#include "main.h"

void initialize_game(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]) {
  // Init playing window.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "tetriC");
  SetTargetFPS(60);

  // Init seed.
  srand(time(NULL));

  // Init grid.
  for (int i = 0; i < GRID_WIDTH; i++) {
    for (int j = 0; j < GRID_HEIGHT; j++) {
      grid[i][j].type = empty;
    }
  }
}

