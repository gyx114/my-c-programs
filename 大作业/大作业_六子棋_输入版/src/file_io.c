#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int save_game(const GameRecord *record, const char *filename)
{
// Ensure directory exists
#ifdef _WIN32
    system("if not exist data mkdir data >nul 2>&1");
#else
    system("mkdir -p data >/dev/null 2>&1");
#endif

    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Error: Cannot create save file!\n");
        return 0;
    }

    fprintf(file, "=== Six Chess Game Record ===\n");
    fprintf(file, "Date: %s\n", record->date);
    fprintf(file, "Winner: ");
    if (record->winner == BLACK)
    {
        fprintf(file, "Black\n");
    }
    else if (record->winner == WHITE)
    {
        fprintf(file, "White\n");
    }
    else
    {
        fprintf(file, "Draw\n");
    }
    fprintf(file, "Total moves: %d\n", record->move_count);
    fprintf(file, "Move sequence: ");

    for (int i = 0; i < record->move_count; i++)
    {
        fprintf(file, "(%d,%d) ", record->moves[i].x, record->moves[i].y);
    }
    fprintf(file, "\n");

    fprintf(file, "Detailed moves:\n");
    for (int i = 0; i < record->move_count; i++)
    {
        fprintf(file, "Move %d: %s (%d,%d)\n",
                i + 1,
                (i % 2 == 0) ? "Black" : "White",
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
        printf("No saved game records found: %s\n", filename);
        return 0;
    }

    int game_count = 0;
    char line[256];
    int move_index = 0;

    while (game_count < max_records && fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Date:"))
        {
            sscanf(line, "Date: %19[^\n]", records[game_count].date);
        }
        else if (strstr(line, "Winner:"))
        {
            char winner_str[10];
            sscanf(line, "Winner: %9[^\n]", winner_str);
            if (strstr(winner_str, "Black"))
            {
                records[game_count].winner = BLACK;
            }
            else if (strstr(winner_str, "White"))
            {
                records[game_count].winner = WHITE;
            }
            else
            {
                records[game_count].winner = EMPTY;
            }
        }
        else if (strstr(line, "Total moves:"))
        {
            sscanf(line, "Total moves: %d", &records[game_count].move_count);
            move_index = 0;
        }
        else if (strstr(line, "Move ") && strstr(line, ":"))
        {
            // Parse detailed moves
            int move_num, x, y;
            char player_str[10];
            if (sscanf(line, "Move %d: %9s (%d,%d)",
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
        printf("No saved game records.\n");
        return;
    }

    printf("\nGame History (%d games):\n", count);
    printf("=====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("Game #%d:\n", i + 1);
        printf("  Date: %s\n", records[i].date);
        printf("  Winner: ");
        if (records[i].winner == BLACK)
        {
            printf("Black\n");
        }
        else if (records[i].winner == WHITE)
        {
            printf("White\n");
        }
        else
        {
            printf("Draw\n");
        }
        printf("  Total moves: %d\n", records[i].move_count);

        // Show first few moves
        printf("  Moves: ");
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

    printf("Press Enter to return to menu...");
    getchar();
    getchar();
}