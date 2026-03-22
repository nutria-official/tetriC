#include "draw.h"

void draw(struct Grid grid[WIDE][HEIGHT], struct block piece) {
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


