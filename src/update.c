#include "update.h"
#include "main.h"

void update(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece) {
  if(floor_collision(*piece) || tetromino_collision(grid, *piece)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (grid[piece->position.x + j][piece->position.y + i].type == falling) {
          grid[piece->position.x + j][piece->position.y + i].type = scrap;
        }
      }
    }
    *piece = place_block();
  
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (piece->coord[j][i] == falling) {
          grid[piece->position.x + j][i].type = falling;
          grid[piece->position.x + j][i].colour = piece->colour;
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
    piece->position.y++;
    printf("moved down\n");
  }
  clear_lines(grid);
}

bool floor_collision(struct block piece) {
  if (piece.position.y >= GRID_HEIGHT - 4) {
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

void clear_lines(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]) {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    int scrap_spaces = 0;
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (grid[j][i].type == scrap) {
        scrap_spaces++;
      }
    }
    if (scrap_spaces == GRID_WIDTH) {
      for (int k = i; k > 1; k--) {
        for (int l = 0; l < GRID_WIDTH; l++) {
          grid[l][k].colour = grid[l][k - 1].colour;
          grid[l][k].type = grid[l][k - 1].type;
        }
      }
      grid[0][0].type = empty;
    } 
  }
}

void player_inputs(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece, int *frames_between_fall) {
  move_tetromino(grid, piece, frames_between_fall);
  //rotate_tetromino(grid, piece);
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
    piece->position.x++;
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
    piece->position.x--;
  }
  if (IsKeyDown(KEY_DOWN)) {
    *frames_between_fall = 10;
  } else {
    *frames_between_fall = 60;
  }
}

/*void rotate_tetromino(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece) {
  if(IsKeyPressed(KEY_X)) {
    if(piece->tetromino != o || piece->tetromino != i) {
      piece->coord[1]
    }
  }
  else if (IsKeyPressed(KEY_Z))
  {

  }
}*/
