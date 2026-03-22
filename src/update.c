#include "update.h"

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
  clear_lines(grid);
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

void clear_lines(struct Grid grid[WIDE][HEIGHT]) {
  for (int i = 0; i < HEIGHT; i++) {
    int empty_spaces = 0;
    for (int j = 0; j < WIDE; j++) {
      if (grid[j][i].type == scrap) {
        empty_spaces++;
      }
    }
    if (empty_spaces == WIDE) {
      for (int k = i; k > 1; k--) {
        for (int l = 0; l < WIDE; l++) {
          grid[l][k].colour = grid[l][k - 1].colour;
          grid[l][k].type = grid[l][k - 1].type;
        }
      }
    } 
  }
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
