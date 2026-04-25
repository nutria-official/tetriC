#include "draw.h"

void draw(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece) {
  int calibration_width = WINDOW_WIDTH/2 - GRID_WIDTH*SQUARE_EDGE/2;
  int calibration_height = WINDOW_HEIGHT/2 - GRID_HEIGHT*SQUARE_EDGE/2;
  BeginDrawing();
  ClearBackground(RAYWHITE);
  // Draw map.
  DrawRectangle(calibration_width, calibration_height, GRID_WIDTH*SQUARE_EDGE, GRID_HEIGHT*SQUARE_EDGE, BLACK);
  // Draw blocks,
    for (int i = 0; i < GRID_HEIGHT; i++) {
      for (int j = 0; j < GRID_WIDTH; j++) {
        if (grid[j][i].type == falling || grid[j][i].type == scrap) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
  EndDrawing();
  int this_colour = ColorToInt(piece.colour);
  printf("Colour: %d\n", this_colour);
  printf("coord.y: %d\n", piece.position.y);
}


