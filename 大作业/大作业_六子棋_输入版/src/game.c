#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "ai.h"
#include "file_io.h"

void show_menu()
{
    printf("\n=====================================\n");
    printf("           六子棋游戏\n");
    printf("=====================================\n");
    printf("1. 玩家对战 (PvP)\n");
    printf("2. 人机对战 (PvAI)\n");
    printf("3. 查看历史对局\n");
    printf("4. 退出游戏\n");
    printf("=====================================\n");
}

void start_game(Game *game, int mode)
{
    init_board(&game->board);
    game->state = PLAYING;
    game->game_mode = mode;
    game->ai_difficulty = MEDIUM;

    if (mode == 1)
    {
        printf("\n选择AI难度:\n");
        printf("1. 简单\n");
        printf("2. 中等\n");
        printf("3. 困难\n");
        printf("请选择 (1-3): ");

        int difficulty;
        if (scanf("%d", &difficulty) == 1 && difficulty >= 1 && difficulty <= 3)
        {
            game->ai_difficulty = difficulty - 1;
        }
        else
        {
            printf("使用默认难度: 中等\n");
        }
    }

    printf("\n游戏开始！\n");
    printf("黑棋: X, 白棋: O\n");
    printf("棋盘坐标: 行(0-14) 列(0-14)\n");

    GameRecord record;
    record.move_count = 0;
    record.winner = EMPTY;

    time_t now = time(NULL);
    strftime(record.date, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

    while (game->state == PLAYING)
    {
        print_board(&game->board);

        int x, y;
        int valid_move = 0;

        if (game->game_mode == 1 && get_current_player(&game->board) == WHITE)
        {
            printf("AI思考中...\n");
            Position ai_move = ai_make_move(&game->board, game->ai_difficulty);
            x = ai_move.x;
            y = ai_move.y;
            printf("AI落子位置: %d %d\n", x, y);
            valid_move = 1;
        }
        else
        {
            while (!valid_move)
            {
                printf("请输入落子坐标 (行 列): ");
                if (scanf("%d %d", &x, &y) != 2)
                {
                    printf("输入格式错误！请使用: 行号 列号 (例如: 7 7)\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }

                if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
                {
                    printf("坐标超出范围！请输入 0 到 %d 之间的数字。\n", BOARD_SIZE - 1);
                    continue;
                }

                valid_move = 1;
            }
        }

        if (!make_move(&game->board, x, y))
        {
            printf("无效移动！该位置已有棋子。\n");
            continue;
        }

        if (record.move_count < BOARD_SIZE * BOARD_SIZE)
        {
            record.moves[record.move_count].x = x;
            record.moves[record.move_count].y = y;
            record.move_count++;
        }

        int winner = check_win(&game->board, x, y);
        if (winner)
        {
            print_board(&game->board);
            printf("\n游戏结束！");
            if (winner == BLACK)
            {
                printf("黑棋获胜！\n");
                record.winner = BLACK;
            }
            else
            {
                printf("白棋获胜！\n");
                record.winner = WHITE;
            }
            printf("总步数: %d\n", record.move_count);

            if (save_game(&record, "data/saved_games.txt"))
            {
                printf("对局已保存到 data/saved_games.txt\n");
            }

            game->state = GAME_OVER;
            break;
        }

        if (record.move_count >= BOARD_SIZE * BOARD_SIZE)
        {
            print_board(&game->board);
            printf("\n平局！棋盘已满。\n");
            record.winner = EMPTY;
            game->state = GAME_OVER;
            break;
        }

        switch_player(&game->board);
    }

    printf("\n按回车键返回主菜单...");
    getchar();
    getchar();
}

void end_game(Game *game)
{
    game->state = GAME_OVER;
}