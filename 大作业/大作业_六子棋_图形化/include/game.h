#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef enum
{
    MENU,
    PLAYING,
    GAME_OVER
} GameState;

typedef enum
{
    MODE_PVP,
    MODE_PVE
} GameMode;

typedef enum
{
    EASY,
    MEDIUM,
    HARD
} Difficulty;

typedef struct
{
    Position moves[BOARD_SIZE * BOARD_SIZE];
    int move_count;
    int winner;
    char date[20];
} GameRecord;

typedef struct
{
    Board board;
    GameState state;
    GameMode game_mode;
    Difficulty ai_difficulty;
    GameRecord current_record;
} Game;

void init_game(Game *game);
void start_game(Game *game, GameMode mode);
void make_game_move(Game *game, int x, int y);
int is_game_over(Game *game);

#endif