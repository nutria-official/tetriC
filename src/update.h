#ifndef UPDATE_H
#define UPDATE_H

#include "main.h"

void update(struct Grid grid[WIDE][HEIGHT], struct block *piece);
void player_inputs(struct Grid grid[WIDE][HEIGHT], struct block *piece);
bool floor_collision(struct block piece);
bool tetromino_collision(struct Grid grid[WIDE][HEIGHT], struct block piece);
void clear_lines(struct Grid grid[WIDE][HEIGHT]);


#endif
