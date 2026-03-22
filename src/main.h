#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
#include <stdlib.h>

#define WIDE 10 // The playing grids horizontal length.
#define HEIGHT 24 // The playing grids vertical length.
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define SQUARE_EDGE 30 // Amount of pixels one side of a drawn square is wide.

struct block place_block();

enum tetrominoes {
  t,
  i,
  l,
  j,
  z,
  s,
  o,
  oops,
};
enum types {
  empty,
  falling,
  scrap,
};
struct coordinate {
  int x;
  int y;
};

struct Grid {
  enum types type;
  struct Color colour;
};

struct block {
  struct coordinate coord[4];
  enum tetrominoes tetromino;
  struct Color colour;
};


#endif
