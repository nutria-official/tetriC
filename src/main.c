#include "main.h"
#include "draw.h"
#include "update.h"
#include "init.h"
#include <raylib.h>
#include <stdlib.h>

struct block place_block();
int gamestate = menu;
int frame_rate = 60;

int main() {
  // Init playing window.
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "tetriC");
  SetTargetFPS(frame_rate);

  int frame_counter = 0;
  int frames_between_fall = frame_rate;
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

  while(!WindowShouldClose()) {
    frame_counter++;
    if (gamestate == playing) {
      player_inputs(grid, &piece, &frames_between_fall);
      if (frame_counter >= frames_between_fall) {
        update(grid, &piece, &frames_between_fall);
        frame_counter = 0;
      }
      draw_game(grid, piece);
    } else if (gamestate == dead) {
      draw_dead(grid);
      if(IsKeyPressed(KEY_SPACE)) {
        gamestate = menu;
      }
      if(IsKeyPressed(KEY_ENTER)) {
        gamestate = playing;
        piece = place_block();
        initialize_game(grid);
      }
    } else if (gamestate == menu) {
      draw_menu(grid);
      if(IsKeyPressed(KEY_SPACE)) {
        gamestate = playing;
        piece = place_block();
        initialize_game(grid);
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            if (piece.coord[j][i] == falling) {
              grid[piece.position.x + j][i].type = falling;
              grid[piece.position.x + j][i].colour = piece.colour;
            }
          }
        }
      }
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
