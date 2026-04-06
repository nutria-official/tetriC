#include "main.h"
#include "draw.h"
#include "update.h"
#include "init.h"

struct block place_block();

int main() {
  int frame_counter = 0;
  int speed = 60;
  struct Grid grid[GRID_WIDTH][GRID_HEIGHT];
  struct block piece = place_block();

  initialize_game(grid);
  draw(grid, piece);

  while(!WindowShouldClose()) {
    frame_counter++;
    player_inputs(grid, &piece, &speed);
    if (frame_counter >= speed) {
      update(grid, &piece);
      frame_counter = 0;
    }
    draw(grid, piece);
  }
  CloseWindow();
  return 0;
}

struct block place_block() {
  struct block piece;
  piece.tetromino = rand() % 7;
  switch (piece.tetromino) {
    case t:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 4;
      piece.coord[1].y = 1;

      piece.coord[2].x = 5;
      piece.coord[2].y = 1;

      piece.coord[3].x = 6;
      piece.coord[3].y = 1;
      break;
    case i:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 5;
      piece.coord[1].y = 1;

      piece.coord[2].x = 5;
      piece.coord[2].y = 2;

      piece.coord[3].x = 5;
      piece.coord[3].y = 3;
      break;
    case l:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 5;
      piece.coord[1].y = 1;

      piece.coord[2].x = 5;
      piece.coord[2].y = 2;

      piece.coord[3].x = 6;
      piece.coord[3].y = 2;
      break;
    case j:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 5;
      piece.coord[1].y = 1;

      piece.coord[2].x = 4;
      piece.coord[2].y = 2;

      piece.coord[3].x = 5;
      piece.coord[3].y = 2;
      break;
    case z:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256,255};
      piece.coord[0].x = 4;
      piece.coord[0].y = 0;

      piece.coord[1].x = 5;
      piece.coord[1].y = 0;

      piece.coord[2].x = 5;
      piece.coord[2].y = 1;

      piece.coord[3].x = 6;
      piece.coord[3].y = 1;
      break;
    case s:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 6;
      piece.coord[1].y = 0;

      piece.coord[2].x = 4;
      piece.coord[2].y = 1;

      piece.coord[3].x = 5;
      piece.coord[3].y = 1;
      break;
    case o:
      piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 6;
      piece.coord[1].y = 0;

      piece.coord[2].x = 5;
      piece.coord[2].y = 1;

      piece.coord[3].x = 6;
      piece.coord[3].y = 1;
      break;
    default:
      piece.tetromino = oops;
      break;
  }
  return piece;
}
