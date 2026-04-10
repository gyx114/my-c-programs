#ifndef GAME_H
#define GAME_H

#include "board.h"

// 游戏状态
typedef enum
{
    MENU,
    PLAYING,
    GAME_OVER,
    REPLAY
} GameState;

// 游戏记录
typedef struct
{
    Position moves[BOARD_SIZE * BOARD_SIZE];
    int move_count;
    int winner;
    char date[20];
} GameRecord;

// 游戏主结构
typedef struct
{
    Board board;
    GameState state;
    int game_mode; // 0: PvP, 1: PvAI
    int ai_difficulty;
} Game;

// 函数声明
void show_menu();
void start_game(Game *game, int mode);
void end_game(Game *game);
void handle_input(Game *game);

#endif