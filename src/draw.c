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
    DrawText(TextFormat("Press space to start"), calibration_width, GRID_HEIGHT*SQUARE_EDGE/2, 20, RED);
    
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
        if (grid[j][i].type == falling || grid[j][i].type == scrap) {
          DrawRectangle(calibration_width + j * SQUARE_EDGE, calibration_height + i * SQUARE_EDGE, SQUARE_EDGE, SQUARE_EDGE, grid[j][i].colour);
        }
      }
    }
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
    DrawText(TextFormat("Press space to menu\n Press enter to game"), calibration_width, GRID_HEIGHT*SQUARE_EDGE/2, 20, RED);
  EndDrawing();
}

