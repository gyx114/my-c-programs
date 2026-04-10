#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "game.h"
#include "file_io.h"

// 设置控制台编码
void set_console_encoding()
{
    system("chcp 65001 > nul");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

int main()
{
    set_console_encoding();

    Game game;
    int choice;

    printf("=====================================\n");
    printf("           六子棋游戏\n");
    printf("=====================================\n");

    while (1)
    {
        show_menu();
        printf("请选择操作: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("输入错误，请重新输入！\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            start_game(&game, 0);
            break;
        case 2:
            start_game(&game, 1);
            break;
        case 3:
            display_saved_games("data/saved_games.txt");
            break;
        case 4:
            printf("感谢游戏！再见！\n");
            return 0;
        default:
            printf("无效选择，请重新输入！\n");
        }
    }

    return 0;
}