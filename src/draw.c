#include "draw.h"
#include "main.h"
#include <raylib.h>

int calibration_width = WINDOW_WIDTH/2 - GRID_WIDTH*SQUARE_EDGE/2;
int calibration_height = WINDOW_HEIGHT/2 - GRID_HEIGHT*SQUARE_EDGE/2;

void draw_menu(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]) {
  BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(calibration_width, calibration_height, GRID_WIDTH*SQUARE_EDGE, GRID_HEIGHT*SQUARE_EDGE, BLACK);
    for (int i = 0; i < GRID_HEIGHT; i++) {
      for (int j = 0; j < GRID_WIDTH; j++) {
        if (grid[j][i].type == scrap) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
    DrawRectangle(calibration_width, calibration_height + GRID_HEIGHT*SQUARE_EDGE/2 - SQUARE_EDGE * 2, GRID_WIDTH*SQUARE_EDGE, SQUARE_EDGE * 4, GREEN);
    DrawText(TextFormat("Press enter to start"), calibration_width + 40, GRID_HEIGHT*SQUARE_EDGE/2 - 20, 20, RED);
    
  EndDrawing();
}

void draw_game(struct Grid grid[GRID_WIDTH][GRID_HEIGHT], struct block piece) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  // Draw map.
  DrawRectangle(calibration_width, calibration_height, GRID_WIDTH*SQUARE_EDGE, GRID_HEIGHT*SQUARE_EDGE, BLACK);
  // Draw blocks,
    for (int i = 0; i < GRID_HEIGHT; i++) {
      for (int j = 0; j < GRID_WIDTH; j++) {
        if (grid[j][i].type == falling || grid[j][i].type == scrap || grid[j][i].type == shadow) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
  DrawRectangle(calibration_width + GRID_WIDTH*SQUARE_EDGE + SQUARE_EDGE, calibration_height, SQUARE_EDGE * 4, GRID_HEIGHT*SQUARE_EDGE/4, BLACK);
  DrawText(TextFormat("Score: %d", score), calibration_width + GRID_WIDTH*SQUARE_EDGE + SQUARE_EDGE, calibration_height, 20, RED);
  EndDrawing();
}

void draw_dead(struct Grid grid[GRID_WIDTH][GRID_HEIGHT]) {
  BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(calibration_width, calibration_height, GRID_WIDTH*SQUARE_EDGE, GRID_HEIGHT*SQUARE_EDGE, BLACK);
    for (int i = 0; i < GRID_HEIGHT; i++) {
      for (int j = 0; j < GRID_WIDTH; j++) {
        if (grid[j][i].type == scrap) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
    DrawRectangle(calibration_width, calibration_height + GRID_HEIGHT*SQUARE_EDGE/2 - SQUARE_EDGE * 2, GRID_WIDTH*SQUARE_EDGE, SQUARE_EDGE * 4, GREEN);
    DrawText(TextFormat("Press enter to menu\nPress space to game\nScore: %d", score), calibration_width + 40, GRID_HEIGHT*SQUARE_EDGE/2 - 20, 20, RED);
  EndDrawing();
}

