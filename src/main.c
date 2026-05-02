#include "main.h"
#include "draw.h"
#include "update.h"
#include "init.h"
#include <stdlib.h>

struct block place_block();
int gamestate = playing;

int main() {
  int frame_counter = 0;
  int frames_between_fall = 60;
  struct Grid grid[GRID_WIDTH][GRID_HEIGHT];
  initialize_game(grid);
  struct block piece = place_block();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece.coord[j][i] == falling) {
        grid[piece.position.x + j][i].type = falling;
        grid[piece.position.x + j][i].colour = piece.colour;
      }
    }
  }

  draw(grid, piece);

  while(!WindowShouldClose()) {
    frame_counter++;
    if (gamestate == playing) {
      player_inputs(grid, &piece, &frames_between_fall);
      if (frame_counter >= frames_between_fall) {
        update(grid, &piece, &frames_between_fall);
        frame_counter = 0;
      }
      draw(grid, piece);
    } else if (gamestate == dead) {
      for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
        grid[i][j].type = empty;
        }
      }
      draw(grid, piece);
    }
  }
  CloseWindow();
  return 0;
}

struct block place_block() {
  struct block piece;

  piece.colour = (Color){rand()%256,rand()%256,rand()%256, 255};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
       piece.coord[j][i] = empty;
    }
  }

  struct coordinates sub_coord;
  sub_coord.x = rand() % 2 + 1; // For balancing s and z piece.
  sub_coord.y = 0;

  piece.coord[sub_coord.x][sub_coord.y] = falling;

  for (int i = 0; i < 3; i++) {
    sub_coord = place_sub_block(piece, sub_coord);
    piece.coord[sub_coord.x][sub_coord.y] = falling;
  }
  piece.position.x = 3;
  piece.position.y = 0;
  printf("placed block\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if(piece.coord[j][i] == falling) {
        printf("x: %d y: %d\n", j, i);
      }
    }
  }
  return piece;
}

struct coordinates place_sub_block(struct block piece, struct coordinates sub_coord) {
  struct coordinates new_coord = sub_coord;
   int direction = rand()%4;
   switch(direction) {
    case up:
      new_coord.y -=1;
      break;
    case down:
      new_coord.y +=1;
      break;
    case left:
      new_coord.x -=1;
      break;
    case right:
      new_coord.x +=1;
      break;
    default:
      printf("This should not happen\n");
      break;
   }
  if (new_coord.x >= 0 &&
      new_coord.x < 4  &&
      new_coord.y >= 0 &&
      new_coord.y < 4)
  {
    if (piece.coord[new_coord.x][new_coord.y] != falling) {
      return new_coord;
    } else {
      return place_sub_block(piece, new_coord);
    }
  }
  return place_sub_block(piece, sub_coord);
}

long int power(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  } 
  int result = base;
  for (int i = 1; i < exponent; i++) {
    result *= base;
  }
  return result;
}

