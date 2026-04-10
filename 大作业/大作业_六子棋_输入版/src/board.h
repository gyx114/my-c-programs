#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 15
#define EMPTY 0
#define BLACK 1
#define WHITE 2

// 棋盘结构
typedef struct
{
    int grid[BOARD_SIZE][BOARD_SIZE];
    int current_player;
} Board;

// 坐标结构
typedef struct
{
    int x;
    int y;
} Position;

// 函数声明
void init_board(Board *board);
void print_board(const Board *board);
int is_valid_move(const Board *board, int x, int y);
int make_move(Board *board, int x, int y);
int check_win(const Board *board, int x, int y);
void switch_player(Board *board);
int get_current_player(const Board *board);

#endif