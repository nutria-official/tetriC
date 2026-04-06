#include "update.h"

void update(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece) {
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
  clear_lines(grid);
}

bool floor_collision(struct block piece) {
  if (piece.coord[3].y == GRID_HEIGHT - 1) {
  return true; 
  }
  return false;
}


bool tetromino_collision(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece) {
  for (int i = 0; i < 4; i++) {
    if (grid[piece.coord[i].x][piece.coord[i].y + 1].type == scrap) {
      return true;
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

void player_inputs(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece, int *speed) {
  move_tetromino(grid, piece, speed);
  rotate_tetromino(grid, piece);
}

void move_tetromino(struct Grid (*grid)[24], struct block *piece, int *speed) {
  if (IsKeyPressed(KEY_RIGHT)
    && ((piece->coord[0].x < GRID_WIDTH - 1
    && piece->coord[1].x < GRID_WIDTH - 1
    && piece->coord[2].x < GRID_WIDTH - 1
    && piece->coord[3].x < GRID_WIDTH - 1
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
  if (IsKeyDown(KEY_DOWN)) {
    *speed = 5;
  } else {
    *speed = 60;
  }
}

void rotate_tetromino(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece) {
    
}
