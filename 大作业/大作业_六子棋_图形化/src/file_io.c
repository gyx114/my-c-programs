#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int save_game(const GameRecord *record, const char *filename)
{
    // 确保目录存在
#ifdef _WIN32
    system("if not exist data mkdir data >nul 2>&1");
#else
    system("mkdir -p data >/dev/null 2>&1");
#endif

    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("错误：无法创建保存文件！\n");
        return 0;
    }

    fprintf(file, "=== 六子棋对局记录 ===\n");
    fprintf(file, "日期: %s\n", record->date);
    fprintf(file, "获胜方: ");
    if (record->winner == BLACK)
    {
        fprintf(file, "黑棋\n");
    }
    else if (record->winner == WHITE)
    {
        fprintf(file, "白棋\n");
    }
    else
    {
        fprintf(file, "平局\n");
    }
    fprintf(file, "总步数: %d\n", record->move_count);
    fprintf(file, "落子序列: ");

    for (int i = 0; i < record->move_count; i++)
    {
        fprintf(file, "(%d,%d) ", record->moves[i].x, record->moves[i].y);
    }
    fprintf(file, "\n");

    fprintf(file, "详细落子记录:\n");
    for (int i = 0; i < record->move_count; i++)
    {
        fprintf(file, "第%d步: %s (%d,%d)\n",
                i + 1,
                (i % 2 == 0) ? "黑棋" : "白棋",
                record->moves[i].x,
                record->moves[i].y);
    }

    fprintf(file, "=====================\n\n");
    fclose(file);
    return 1;
}

int load_games(GameRecord *records, int max_records, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("未找到保存的对局记录: %s\n", filename);
        return 0;
    }

    int game_count = 0;
    char line[256];
    int move_index = 0;

    while (game_count < max_records && fgets(line, sizeof(line), file))
    {
        if (strstr(line, "日期:"))
        {
            sscanf(line, "日期: %19[^\n]", records[game_count].date);
        }
        else if (strstr(line, "获胜方:"))
        {
            char winner_str[10];
            sscanf(line, "获胜方: %9[^\n]", winner_str);
            if (strstr(winner_str, "黑棋"))
            {
                records[game_count].winner = BLACK;
            }
            else if (strstr(winner_str, "白棋"))
            {
                records[game_count].winner = WHITE;
            }
            else
            {
                records[game_count].winner = EMPTY;
            }
        }
        else if (strstr(line, "总步数:"))
        {
            sscanf(line, "总步数: %d", &records[game_count].move_count);
            move_index = 0;
        }
        else if (strstr(line, "第") && strstr(line, "步:"))
        {
            // 解析详细落子记录
            int move_num, x, y;
            char player_str[10];
            if (sscanf(line, "第%d步: %9s (%d,%d)",
                       &move_num, player_str, &x, &y) == 4)
            {
                if (move_index < records[game_count].move_count)
                {
                    records[game_count].moves[move_index].x = x;
                    records[game_count].moves[move_index].y = y;
                    move_index++;
                }
            }
        }
        else if (strstr(line, "====================="))
        {
            game_count++;
        }
    }

    fclose(file);
    return game_count;
}

void display_saved_games(const char *filename)
{
    GameRecord records[100];
    int count = load_games(records, 100, filename);

    if (count == 0)
    {
        printf("没有保存的对局记录。\n");
        return;
    }

    printf("\n对局历史记录 (%d 局):\n", count);
    printf("=====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("对局 #%d:\n", i + 1);
        printf("  日期: %s\n", records[i].date);
        printf("  获胜方: ");
        if (records[i].winner == BLACK)
        {
            printf("黑棋\n");
        }
        else if (records[i].winner == WHITE)
        {
            printf("白棋\n");
        }
        else
        {
            printf("平局\n");
        }
        printf("  总步数: %d\n", records[i].move_count);

        // 显示前几步
        printf("  落子: ");
        for (int j = 0; j < (records[i].move_count < 6 ? records[i].move_count : 6); j++)
        {
            printf("(%d,%d) ", records[i].moves[j].x, records[i].moves[j].y);
        }
        if (records[i].move_count > 6)
        {
            printf("...");
        }
        printf("\n");
        printf("-------------------------------------\n");
    }

    printf("按回车键返回菜单...");
    getchar();
    getchar();
}