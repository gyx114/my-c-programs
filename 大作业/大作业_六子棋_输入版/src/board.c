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

void print_board(const Board *board)
{
    printf("\n");

    // 顶部列标 - 精确对齐每个格子中心
    // 每个格子3字符宽度，数字应该在第2个字符位置
    printf("    ");
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (j < 10)
        {
            printf(" %d  ", j); // 个位数：前后各1空格
        }

        else
        {
            if (j == 10)
            {
                printf(" ");
            }
            printf("%d  ", j); // 两位数：前面0空格，后面2空格
        }
    }
    printf("\n");

    // 顶部边框
    printf("   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // 行标和左边框
        printf("%2d │", i);

        // 棋盘内容
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->grid[i][j] == EMPTY)
            {
                printf("   ");
            }
            else if (board->grid[i][j] == BLACK)
            {
                printf(" ● ");
            }
            else
            {
                printf(" ○ ");
            }

            if (j < BOARD_SIZE - 1)
            {
                printf("│");
            }
        }

        // 右边框和行标
        printf("│ %2d\n", i);

        // 行间分隔线
        if (i < BOARD_SIZE - 1)
        {
            printf("   ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
        }
    }

    // 底部边框
    printf("   └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");

    // 底部列标 - 精确对齐
    printf("    ");
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (j < 10)
        {
            printf(" %d  ", j); // 个位数：前后各1空格
        }

        else
        {
            if (j == 10)
            {
                printf(" ");
            }
            printf("%d  ", j); // 两位数：前面0空格，后面2空格
        }
    }
    printf("\n");

    printf("\n当前玩家: %s\n", board->current_player == BLACK ? "黑棋●" : "白棋○");
    printf("输入格式: 行 列 (0-14, 例如: 7 7)\n");
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

    // 检查方向: 水平、垂直、左上右下、右上左下
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