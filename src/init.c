#include "init.h"

void initialize_game(struct Grid grid[WIDE][HEIGHT]) {

  // Init playing window.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "tetriC");
  SetTargetFPS(60);

  // Init seed.
  srand(time(NULL));

  // Init grid.
  for (int i = 0; i < WIDE; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j].type = empty;
    }
  }
}

