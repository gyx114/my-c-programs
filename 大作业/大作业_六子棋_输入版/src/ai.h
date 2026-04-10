#ifndef AI_H
#define AI_H

#include "board.h"

// AI难度级别
typedef enum
{
    EASY,
    MEDIUM,
    HARD
} Difficulty;

// 函数声明
Position ai_make_move(const Board *board, Difficulty difficulty);
int evaluate_position_score(const Board *board, int x, int y, int player);
int find_winning_move(const Board *board, int player, Position *move);
int find_blocking_move(const Board *board, int player, Position *move);

#endif