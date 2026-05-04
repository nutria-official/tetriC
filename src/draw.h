#ifndef DRAW_H
#define DRAW_H
#include "main.h"

void draw_menu(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]);
void draw_game(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece);
void draw_dead(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]);

#endif


