#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>

#define WINDOW_HEIGHT 24 * (2 + 20)
#define WINDOW_WIDTH 10 * (2 + 20)

enum tetrominoes {
  t,
  i,
  l,
  j,
  z,
  s,
  o,
  empty,
};

struct coordinate {
  int x;
  int y;
};

struct block {
  struct coordinate coord[4];
  enum tetrominoes tetromino;
};

struct block place_block();
void update(bool grid[10][24], struct block *piece);
void player_input(bool grid[10][24], struct block *piece);
bool floor_collision(struct block piece);
bool tetromino_collision(bool grid[10][24], struct block piece);
void print_board(bool grid [10][24], struct block piece);

int main() {
  srand(time(NULL));
  bool grid[10][24] = {false};
  struct block piece = place_block();
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "tetrC");
  SetTargetFPS(60);

  print_board(grid, piece);
  while(!WindowShouldClose()) {
    sleep(1);
    //player_input(grid, &piece);
    update(grid, &piece);
    print_board(grid, piece);
  }
  CloseWindow();
  return 0;
}

struct block place_block() {
  struct block piece;
  piece.tetromino = rand() % 7;
  switch (piece.tetromino) {
    case t:
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
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 5;
      piece.coord[1].y = 1;

      piece.coord[2].x = 5;
      piece.coord[2].y = 2;

      piece.coord[3].x = 4;
      piece.coord[3].y = 2;
      break;
    case z:
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
      piece.coord[0].x = 5;
      piece.coord[0].y = 0;

      piece.coord[1].x = 6;
      piece.coord[1].y = 0;

      piece.coord[2].x = 5;
      piece.coord[2].y = 1;

      piece.coord[3].x = 4;
      piece.coord[3].y = 1;
      break;
    case o:
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
      piece.tetromino = empty;
      break;
  }
  return piece;
}

void update(bool grid[10][24], struct block *piece) {
  if(floor_collision(*piece) || tetromino_collision(grid, *piece)) {
    *piece = place_block();
  } else {
    for (int i = 3; i >= 0; i--){
      grid[piece->coord[i].x][piece->coord[i].y] = false;
      piece->coord[i].y++; 
      grid[piece->coord[i].x][piece->coord[i].y] = true;
    }
  }
}

void print_board(bool grid[10][24], struct block piece) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 10; j++) {
        DrawRectangle(i, j, 20, 20, RED); 
      }
    }
  EndDrawing();
}

bool floor_collision(struct block piece) {
  if (piece.coord[3].y == 23) {
  return true; 
  }
  return false;
}


bool tetromino_collision(bool grid[10][24], struct block piece) {
  for (int i = 0; i < 4; i++) {
    if (grid[piece.coord[i].x][piece.coord[i].y + 1] == true
        && piece.coord[i].y + 1 != piece.coord[0].y
        && piece.coord[i].y + 1 != piece.coord[1].y
        && piece.coord[i].y + 1 != piece.coord[2].y
        && piece.coord[i].y + 1 != piece.coord[3].y
    ) {
      return true;
    }
  }
  return false;
}


//void player_input(struct block grid[10][24], struct coordinate block[4]) {
//  char input;
//  fgets()
//}



