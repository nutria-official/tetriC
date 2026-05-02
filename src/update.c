#include "update.h"
#include "main.h"

long int score = 0;
static int cleared_lines_total = 0;

void update(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece, int* frames_between_fall) {
  if(floor_collision(*piece) || tetromino_collision(grid, *piece)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (grid[piece->position.x + j][piece->position.y + i].type == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = scrap;
        }
      }
    }
    clear_lines(grid, frames_between_fall);
    *piece = place_block();
  
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (grid[piece->position.x + j][piece->position.y + i].type == scrap) {
          gamestate = dead;
          printf("You dead fr bruh, git gut\n");
        }
        if (piece->coord[j][i] == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = falling;
          grid[piece->position.x + j][piece->position.y + i].colour = piece->colour;
        }
      }
    }

  } else {
    for (int i = 3; i >= 0; i--) {
      for (int j = 3; j >= 0; j--) {
        if (grid[piece->position.x + j][piece->position.y + i].type == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = empty;
          grid[piece->position.x + j][piece->position.y + i + 1].type = falling;
          grid[piece->position.x + j][piece->position.y + i + 1].colour = piece->colour;
        } 
      }
    }
    if (piece->position.y + 4 < GRID_HEIGHT) {
      piece->position.y++;
    } else {
      for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
          if (piece->coord[j][i] == falling) {
            piece->coord[j][i] = empty;
            piece->coord[j][i + 1] = falling;
          }
        }
      }
    }
    printf("score: %ld\n", score);
  }
}

bool floor_collision(struct block piece) {
  if (piece.position.y >= GRID_HEIGHT - 5) {
    for (int i = 3; i >= 0; i--) {
      for (int j = 3; j >= 0; j--) {
        if (piece.coord[j][i] == falling && i + piece.position.y == GRID_HEIGHT - 1) {
          return true;
        }
      }
    }
  }
  return false;
}

bool tetromino_collision(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece) {
  int counter_of_falling = 0; // Due to the matrix being 4*4 and the tetromino withins position is not known.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (counter_of_falling > 4) {
        return false;
      } else {
        if (grid[piece.position.x + j][piece.position.y + i].type == falling) {
          counter_of_falling++;
          if (grid[piece.position.x + j][piece.position.y + i + 1].type == scrap) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void clear_lines(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], int* frames_between_fall) {
  int cleared_lines = 0; // From 0 to 4.
  for (int i = 0; i < GRID_HEIGHT; i++) {
    int scrap_spaces = 0;
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (grid[j][i].type == scrap) {
        scrap_spaces++;
      }
    }
    if (scrap_spaces == GRID_WIDTH) {
      cleared_lines++;
      cleared_lines_total++;
      for (int k = i; k > 0; k--) {
        for (int l = 0; l < GRID_WIDTH; l++) {
          grid[l][k].colour = grid[l][k - 1].colour;
          grid[l][k].type = grid[l][k - 1].type;
        }
      }
    } 
  }
  if (cleared_lines > 0) {
    score = score + power(2, cleared_lines_total) * power(2,cleared_lines);
  }
}

void player_inputs(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece, int *frames_between_fall) {
  move_tetromino(grid, piece, frames_between_fall);
  rotate_tetromino(grid, piece);
}

void move_tetromino(struct Grid (*grid)[24], struct block *piece, int *frames_between_fall) {
  int leftest_coord = 3;
  int rightest_coord = 0;
  bool can_move_left = true;
  bool can_move_right = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece->coord[j][i] == falling) {
        if (j < leftest_coord) {
          leftest_coord = j;
        }
        if (j > rightest_coord) {
          rightest_coord = j;
        }
        if (piece->position.x + leftest_coord == 0 || grid[piece->position.x + j - 1][piece->position.y + i].type == scrap) {
         can_move_left = false; 
        }
        if (piece->position.x + rightest_coord == GRID_WIDTH - 1 || grid[piece->position.x + j + 1][piece->position.y + i].type == scrap) {
         can_move_right = false; 
        }
      }
    }
  }
  if (IsKeyPressed(KEY_RIGHT) && can_move_right) {
    for (int i = 3; i >= 0; i--) { // -- do to the way that the tetromino_subsquares are drawn.
      for (int j = 3; j >=0; j--) {
        if (piece->coord[j][i] == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = empty;
          grid[piece->position.x + j + 1][piece->position.y + i].type = falling;
          grid[piece->position.x + j + 1][piece->position.y + i].colour = piece->colour;
        }
      }
    }
    if(piece->position.x + 4 < GRID_WIDTH) {
      piece->position.x++;
    } else {
      if(rightest_coord != 3 ) {
        for (int i = 3; i >= 0; i--) {
          for (int j = 3; j >= 0; j--) {
            if (piece->coord[j][i] == falling) {
              piece->coord[j][i] = empty;
              piece->coord[j + 1][i] = falling;
            }
          }
        }
      }
    }
  } else if (IsKeyPressed(KEY_LEFT) && can_move_left) {
    for (int i = 0; i < 4; i++) { // -- do to the way that the tetromino_subsquares are drawn.
      for (int j = 0; j < 4; j++) {
        if (piece->coord[j][i] == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = empty;
          grid[piece->position.x + j - 1][piece->position.y + i].type = falling;
          grid[piece->position.x + j - 1][piece->position.y + i].colour = piece->colour;
        }
      }
    }
    if(piece->position.x > 0) {
      piece->position.x--;
    } else {
      if(leftest_coord != 0) {
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            if (piece->coord[j][i] == falling) {
              piece->coord[j][i] = empty;
              piece->coord[j - 1][i] = falling;
            }
          }
        }
      }
    }
  }
  if (IsKeyDown(KEY_DOWN)) {
    *frames_between_fall = 10;
  } else {
    *frames_between_fall = 60;
  }
}

void rotate_tetromino(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece) {
  bool can_rotate = true;
  if(IsKeyPressed(KEY_X)) {
    struct block rotated_piece;
    rotated_piece.position = piece->position;
    rotated_piece.colour = piece->colour;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (piece->coord[j][i] == falling) {
          if (grid[rotated_piece.position.x - i + 3][rotated_piece.position.y + j].type == scrap) {
            can_rotate = false;
          }
          rotated_piece.coord[-i + 3][j] = falling;
        } else {
          rotated_piece.coord[-i + 3][j] = empty;
        }
      }
    }
    if (can_rotate) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (piece->coord[j][i] == falling) {
            grid[rotated_piece.position.x - i + 3][rotated_piece.position.y + j].type = falling;
            grid[rotated_piece.position.x - i + 3][rotated_piece.position.y + j].colour = rotated_piece.colour;
          } else {
            if (grid[rotated_piece.position.x - i + 3][rotated_piece.position.y + j].type == falling) {
              grid[rotated_piece.position.x - i + 3][rotated_piece.position.y + j].type = empty;
            }
          }
        }
      }
      *piece = rotated_piece;
    }
  }
  can_rotate = true;
  if (IsKeyPressed(KEY_Z))
  {
    struct block rotated_piece;
    rotated_piece.position = piece->position;
    rotated_piece.colour = piece->colour;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (piece->coord[j][i] == falling) {
          if (grid[rotated_piece.position.x + i][rotated_piece.position.y - j + 3].type == scrap) {
            can_rotate = false;
          }
          rotated_piece.coord[i][-j + 3] = falling;
        } else {
          rotated_piece.coord[i][-j + 3] = empty;
        }
      }
    }
    if (can_rotate) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (piece->coord[j][i] == falling) {
            grid[rotated_piece.position.x + i][rotated_piece.position.y - j + 3].type = falling;
            grid[rotated_piece.position.x + i][rotated_piece.position.y - j + 3].colour = rotated_piece.colour;
          } else {
            if (grid[rotated_piece.position.x + i][rotated_piece.position.y - j + 3].type == falling) {
              grid[rotated_piece.position.x + i][rotated_piece.position.y - j + 3].type = empty;
            }
          }
        }
      }
      *piece = rotated_piece;
    }
  }
}
