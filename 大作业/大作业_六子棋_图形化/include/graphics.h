#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>
#include "game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BOARD_MARGIN 50
#define CELL_SIZE 35

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// 核心图形函数
int init_graphics(void);
void cleanup_graphics(void);
void draw_board(const Board *board);
void draw_stones(const Board *board);
void draw_circle_stone(int x, int y, int player);

// 添加点击处理函数声明
void handle_click(Game *game, int mouse_x, int mouse_y);

#endif