#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ai.h"

// 棋型评分表
typedef struct
{
    int score;
    const char *name;
} Pattern;

Pattern patterns[] = {
    {100000, "长连"}, // 6子或以上
    {50000, "连五"},  // 5子
    {10000, "活四"},  // 没有阻挡的四子
    {5000, "冲四"},   // 一头被挡的四子
    {2000, "活三"},   // 没有阻挡的三子
    {1000, "眠三"},   // 一头被挡的三子
    {500, "活二"},    // 没有阻挡的二子
    {100, "眠二"},    // 一头被挡的二子
};

// 检查一个方向的连续棋子
int count_consecutive(const Board *board, int x, int y, int dx, int dy, int player)
{
    int count = 0;
    int nx = x + dx;
    int ny = y + dy;

    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE)
    {
        if (board->grid[nx][ny] == player)
        {
            count++;
            nx += dx;
            ny += dy;
        }
        else
        {
            break;
        }
    }
    return count;
}

// 分析一个位置的棋型
int analyze_position(const Board *board, int x, int y, int player)
{
    if (!is_valid_move(board, x, y))
        return -1;

    int total_score = 0;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];

        // 正向计数
        int forward = count_consecutive(board, x, y, dx, dy, player);
        // 反向计数
        int backward = count_consecutive(board, x, y, -dx, -dy, player);

        int total = forward + backward;

        // 根据连续棋子数量评分
        if (total >= 5)
        {
            total_score += patterns[0].score; // 长连
        }
        else if (total == 4)
        {
            // 检查是否是活四
            int blocked_front = 0, blocked_back = 0;
            int front_x = x + dx * (forward + 1);
            int front_y = y + dy * (forward + 1);
            int back_x = x - dx * (backward + 1);
            int back_y = y - dy * (backward + 1);

            if (front_x < 0 || front_x >= BOARD_SIZE || front_y < 0 || front_y >= BOARD_SIZE ||
                board->grid[front_x][front_y] != EMPTY)
            {
                blocked_front = 1;
            }
            if (back_x < 0 || back_x >= BOARD_SIZE || back_y < 0 || back_y >= BOARD_SIZE ||
                board->grid[back_x][back_y] != EMPTY)
            {
                blocked_back = 1;
            }

            if (!blocked_front && !blocked_back)
            {
                total_score += patterns[2].score; // 活四
            }
            else if (blocked_front && blocked_back)
            {
                // 两头都被挡，实际不可能
            }
            else
            {
                total_score += patterns[3].score; // 冲四
            }
        }
        else if (total == 3)
        {
            // 类似逻辑检查活三/眠三
            total_score += patterns[4].score; // 活三
        }
        else if (total == 2)
        {
            total_score += patterns[6].score; // 活二
        }
    }

    return total_score;
}

// 简单AI：还是随机，但会优先中心
Position ai_make_move_easy(const Board *board)
{
    Position moves[BOARD_SIZE * BOARD_SIZE];
    int move_count = 0;

    // 收集所有空位
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                moves[move_count].x = i;
                moves[move_count].y = j;
                move_count++;
            }
        }
    }

    if (move_count == 0)
    {
        Position default_move = {BOARD_SIZE / 2, BOARD_SIZE / 2};
        return default_move;
    }

    // 优先选择中心区域
    for (int i = 0; i < move_count; i++)
    {
        int dist_to_center = abs(moves[i].x - BOARD_SIZE / 2) + abs(moves[i].y - BOARD_SIZE / 2);
        if (dist_to_center <= 2 && rand() % 3 == 0)
        {
            return moves[i];
        }
    }

    // 否则随机选择
    return moves[rand() % move_count];
}

// 中等AI：能识别基本的威胁和机会
Position ai_make_move_medium(const Board *board)
{
    Position best_move;
    int best_score = -1;

    // 1. 检查自己是否能赢
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                Board test_board = *board;
                test_board.grid[i][j] = WHITE;
                if (check_win(&test_board, i, j))
                {
                    best_move.x = i;
                    best_move.y = j;
                    return best_move;
                }
            }
        }
    }

    // 2. 检查是否需要阻挡玩家（四子威胁）
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                Board test_board = *board;
                test_board.grid[i][j] = BLACK;
                if (check_win(&test_board, i, j))
                {
                    best_move.x = i;
                    best_move.y = j;
                    return best_move;
                }
            }
        }
    }

    // 3. 检查四子威胁（更严格的检查）
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                int threat_score = analyze_position(board, i, j, BLACK);
                if (threat_score >= patterns[2].score)
                { // 活四或冲四威胁
                    best_move.x = i;
                    best_move.y = j;
                    return best_move;
                }
            }
        }
    }

    // 4. 选择最佳进攻位置
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                int score = analyze_position(board, i, j, WHITE);
                if (score > best_score)
                {
                    best_score = score;
                    best_move.x = i;
                    best_move.y = j;
                }
            }
        }
    }

    if (best_score > 0)
    {
        return best_move;
    }

    // 5. 备用方案
    return ai_make_move_easy(board);
}

// 困难AI：真正的棋力
Position ai_make_move_hard(const Board *board)
{
    Position best_move;
    int best_score = -1000000;

    // 1. 检查自己是否能赢
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                Board test_board = *board;
                test_board.grid[i][j] = WHITE;
                if (check_win(&test_board, i, j))
                {
                    best_move.x = i;
                    best_move.y = j;
                    return best_move;
                }
            }
        }
    }

    // 2. 检查玩家威胁（能赢的位置）
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                Board test_board = *board;
                test_board.grid[i][j] = BLACK;
                if (check_win(&test_board, i, j))
                {
                    best_move.x = i;
                    best_move.y = j;
                    return best_move;
                }
            }
        }
    }

    // 3. 综合评估所有位置
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (is_valid_move(board, i, j))
            {
                int attack_score = analyze_position(board, i, j, WHITE);
                int defense_score = analyze_position(board, i, j, BLACK);

                // 防守分数更重要（乘以系数）
                int total_score = attack_score + defense_score * 1.2;

                // 中心位置加分
                int center_dist = abs(i - BOARD_SIZE / 2) + abs(j - BOARD_SIZE / 2);
                total_score += (BOARD_SIZE - center_dist) * 10;

                if (total_score > best_score)
                {
                    best_score = total_score;
                    best_move.x = i;
                    best_move.y = j;
                }
            }
        }
    }

    return best_move;
}

Position ai_make_move(const Board *board, Difficulty difficulty)
{
    static int initialized = 0;
    if (!initialized)
    {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }

    switch (difficulty)
    {
    case EASY:
        return ai_make_move_easy(board);
    case MEDIUM:
        return ai_make_move_medium(board);
    case HARD:
        return ai_make_move_hard(board);
    default:
        return ai_make_move_medium(board);
    }
}