#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "ai.h"
#include "file_io.h"

void init_game(Game *game)
{
    init_board(&game->board);
    game->state = MENU;
    game->game_mode = MODE_PVP;
    game->ai_difficulty = MEDIUM;
    memset(&game->current_record, 0, sizeof(GameRecord));
}

void start_game(Game *game, GameMode mode)
{
    init_board(&game->board);
    game->state = PLAYING;
    game->game_mode = mode;

    // 初始化游戏记录
    game->current_record.move_count = 0;
    game->current_record.winner = EMPTY;
    time_t now = time(NULL);
    strftime(game->current_record.date, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

    printf("游戏开始！模式: %s\n", mode == MODE_PVP ? "玩家对战" : "人机对战");
}

void make_game_move(Game *game, int x, int y)
{
    if (!make_move(&game->board, x, y))
    {
        return;
    }

    // 记录移动
    if (game->current_record.move_count < BOARD_SIZE * BOARD_SIZE)
    {
        game->current_record.moves[game->current_record.move_count].x = x;
        game->current_record.moves[game->current_record.move_count].y = y;
        game->current_record.move_count++;
    }

    // 检查胜负
    int winner = check_win(&game->board, x, y);
    if (winner)
    {
        game->state = GAME_OVER;
        game->current_record.winner = winner;

        // 保存游戏记录
        if (save_game(&game->current_record, "data/saved_games.txt"))
        {
            printf("对局已保存！\n");
        }
        return;
    }

    // 检查平局
    if (game->current_record.move_count >= BOARD_SIZE * BOARD_SIZE)
    {
        game->state = GAME_OVER;
        game->current_record.winner = EMPTY;
        if (save_game(&game->current_record, "data/saved_games.txt"))
        {
            printf("平局对局已保存！\n");
        }
        return;
    }

    switch_player(&game->board);
}

int is_game_over(Game *game)
{
    return game->state == GAME_OVER;
}