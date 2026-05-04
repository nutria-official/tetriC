#ifndef UPDATE_H
#define UPDATE_H

#include "main.h"
#include <math.h>

bool update(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece);
void player_inputs(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece);
bool floor_collision(struct block piece);
bool tetromino_collision(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece);
void clear_lines(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]);
void rotate_tetromino(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece);
void move_tetromino(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block *piece);
void update_shadow(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece);

#endif
