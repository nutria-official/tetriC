#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define SQUARE_EDGE 30
#define WIDE 10
#define HEIGHT 24

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

struct block place_block();
void update(struct Grid grid[WIDE][HEIGHT], struct block *piece);
void player_inputs(struct Grid grid[WIDE][HEIGHT], struct block *piece);
bool floor_collision(struct block piece);
bool tetromino_collision(struct Grid grid[WIDE][HEIGHT], struct block piece);
void print_board(struct Grid[WIDE][HEIGHT], struct block piece);

int main() {
  srand(time(NULL));
  struct Grid grid[WIDE][HEIGHT];
  for (int i = 0; i < WIDE; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      grid[i][j].type = empty;
    }
  }
  struct block piece = place_block();
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "tetriC");
  SetTargetFPS(60);
  int frame_counter = 0;

  print_board(grid, piece);
  while(!WindowShouldClose()) {
    frame_counter++;
    player_inputs(grid, &piece);
    if (frame_counter >= 10) {
      update(grid, &piece);
      frame_counter = 0;
    }
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
      piece.colour = PURPLE;
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
      piece.colour = BLUE;
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
      piece.colour = ORANGE;
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
      piece.colour = BLUE;
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
      piece.colour = RED;
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
      piece.colour = GREEN;
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
      piece.colour = YELLOW;
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

void update(struct Grid grid[WIDE][HEIGHT], struct block *piece) {
  if(floor_collision(*piece) || tetromino_collision(grid, *piece)) {
    for (int i = 3; i >= 0; i--){
      grid[piece->coord[i].x][piece->coord[i].y].type = scrap;
    }
    *piece = place_block();
  } else {
    for (int i = 3; i >= 0; i--){
      grid[piece->coord[i].x][piece->coord[i].y].type = empty;
      piece->coord[i].y++; 
      grid[piece->coord[i].x][piece->coord[i].y].type = falling;
      grid[piece->coord[i].x][piece->coord[i].y].colour = piece->colour;
    }
  }
}

void print_board(struct Grid grid[WIDE][HEIGHT], struct block piece) {
  int calibration_width = WINDOW_WIDTH/2 - WIDE*SQUARE_EDGE/2;
  int calibration_height = WINDOW_HEIGHT/2 - HEIGHT*SQUARE_EDGE/2;
  BeginDrawing();
  ClearBackground(RAYWHITE);
  // Draw map.
  DrawRectangle(calibration_width, calibration_height, WIDE*SQUARE_EDGE, HEIGHT*SQUARE_EDGE, BLACK);
  // Draw blocks,
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDE; j++) {
        if (grid[j][i].type == falling || grid[j][i].type == scrap) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
  EndDrawing();
}

bool floor_collision(struct block piece) {
  if (piece.coord[3].y == HEIGHT - 1) {
  return true; 
  }
  return false;
}


bool tetromino_collision(struct Grid grid[WIDE][HEIGHT], struct block piece) {
  for (int i = 0; i < 4; i++) {
    if (grid[piece.coord[i].x][piece.coord[i].y + 1].type == scrap) {
      return true;
    }
  }
  return false;
}


void player_inputs(struct Grid grid[WIDE][HEIGHT], struct block *piece) {
  if (IsKeyPressed(KEY_RIGHT)
    && ((piece->coord[0].x < WIDE - 1
    && piece->coord[1].x < WIDE - 1
    && piece->coord[2].x < WIDE - 1
    && piece->coord[3].x < WIDE - 1
  )&&(
    grid[piece->coord[0].x + 1][piece->coord[0].y].type != scrap
    && grid[piece->coord[1].x + 1][piece->coord[1].y].type != scrap
    && grid[piece->coord[2].x + 1][piece->coord[2].y].type != scrap
    && grid[piece->coord[3].x + 1][piece->coord[3].y].type != scrap
    )
  )
  ) {
    for (int i = 3; i >= 0; i--) { // -- do to the way that the tetromino_subsquares are drawn.
      grid[piece->coord[i].x][piece->coord[i].y].type = empty;
      piece->coord[i].x++; 
      grid[piece->coord[i].x][piece->coord[i].y].type = falling;
      grid[piece->coord[i].x][piece->coord[i].y].colour = piece->colour;
    }
  } else if (IsKeyPressed(KEY_LEFT)
    && ((piece->coord[0].x > 0
    && piece->coord[1].x > 0
    && piece->coord[2].x > 0
    && piece->coord[3].x > 0
    )&&(
    grid[piece->coord[0].x - 1][piece->coord[0].y].type != scrap
    && grid[piece->coord[1].x - 1][piece->coord[1].y].type != scrap
    && grid[piece->coord[2].x - 1][piece->coord[2].y].type != scrap
    && grid[piece->coord[3].x - 1][piece->coord[3].y].type != scrap
    )
  )
  ) {
    for (int i = 0; i < 4; i++) {
      grid[piece->coord[i].x][piece->coord[i].y].type = empty;
      piece->coord[i].x--; 
      grid[piece->coord[i].x][piece->coord[i].y].type = falling;
      grid[piece->coord[i].x][piece->coord[i].y].colour = piece->colour;
    }
  }
}



