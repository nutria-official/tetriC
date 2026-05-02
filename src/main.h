#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define GRID_WIDTH 10 // The playing grids horizontal length.
#define GRID_HEIGHT 24 // The playing grids vertical length.
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define SQUARE_EDGE 30 // Amount of pixels one side of a drawn square is wide.


struct block place_block();
struct coordinates place_sub_block(struct block piece, struct coordinates sub_coord);
long int power(int base, int exponent);

extern int gamestate;
extern long int score;

enum types {
  empty,
  falling,
  scrap,
};

enum game_states {
  menu,
  playing,
  dead,
};

enum directinos {
  up,
  down,
  left,
  right,
};

struct coordinates {
  int x;
  int y;
};

struct Grid {
  enum types type;
  struct Color colour;
};

struct block {
  enum types coord[4][4]; // Matrix size for all blocks.
  struct Color colour;
  struct coordinates position;
};

#endif
