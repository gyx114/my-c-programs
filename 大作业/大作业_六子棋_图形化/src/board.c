#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void init_board(Board *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board->grid[i][j] = EMPTY;
        }
    }
    board->current_player = BLACK;
}

int is_valid_move(const Board *board, int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
    {
        return 0;
    }
    return board->grid[x][y] == EMPTY;
}

int make_move(Board *board, int x, int y)
{
    if (!is_valid_move(board, x, y))
    {
        return 0;
    }
    board->grid[x][y] = board->current_player;
    return 1;
}

void switch_player(Board *board)
{
    board->current_player = (board->current_player == BLACK) ? WHITE : BLACK;
}

int get_current_player(const Board *board)
{
    return board->current_player;
}

int check_win(const Board *board, int x, int y)
{
    int player = board->grid[x][y];
    if (player == EMPTY)
        return 0;

    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1;

        // 正向检查
        for (int i = 1; i < 6; i++)
        {
            int nx = x + dx * i;
            int ny = y + dy * i;
            if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE)
                break;
            if (board->grid[nx][ny] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }

        // 反向检查
        for (int i = 1; i < 6; i++)
        {
            int nx = x - dx * i;
            int ny = y - dy * i;
            if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE)
                break;
            if (board->grid[nx][ny] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }

        if (count >= 6)
        {
            return player;
        }
    }

    return 0;
}