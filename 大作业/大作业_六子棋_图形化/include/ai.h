#ifndef AI_H
#define AI_H

#include "board.h"
#include "game.h"

Position ai_make_move(const Board *board, Difficulty difficulty);
int analyze_position(const Board *board, int x, int y, int player);

#endif