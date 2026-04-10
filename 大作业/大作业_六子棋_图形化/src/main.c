#include <SDL3/SDL.h>
#include <stdio.h>
#include <windows.h>
#include "graphics.h"
#include "game.h"
#include "ai.h"
#include "file_io.h"

void set_console_encoding()
{
    system("chcp 65001 > nul");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void show_console_menu()
{
    printf("\n=== 六子棋游戏设置 ===\n");
    printf("请选择操作:\n");
    printf("1. 玩家对战 (PvP) - 两人轮流点击下棋\n");
    printf("2. 人机对战 (PvAI) - 玩家点击，AI自动应对\n");
    printf("3. 查看历史对局记录\n");
    printf("4. 退出游戏\n");
    printf("======================\n");
    printf("请选择 (1-4): ");
}

void show_ai_difficulty_menu()
{
    printf("\n选择AI难度:\n");
    printf("1. 简单\n");
    printf("2. 中等\n");
    printf("3. 困难\n");
    printf("请选择 (1-3): ");
}

void show_history_records()
{
    printf("\n正在加载历史记录...\n");
    display_saved_games("data/saved_games.txt");
    printf("按回车键返回主菜单...");
    getchar(); // 等待回车
    getchar(); // 清空缓冲区
}

void setup_game(Game *game)
{
    set_console_encoding();

    printf("六子棋游戏\n");
    printf("==========\n");

    while (1)
    {
        show_console_menu();
        int choice;
        if (scanf("%d", &choice) != 1)
        {
            printf("输入错误！\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1: // PVP
            start_game(game, MODE_PVP);
            printf("玩家对战模式！\n");
            printf("请在SDL窗口中使用鼠标点击下棋\n");
            printf("黑棋先手，轮流点击棋盘位置\n");
            return;
        case 2: // PVE
            show_ai_difficulty_menu();
            int difficulty;
            if (scanf("%d", &difficulty) == 1 && difficulty >= 1 && difficulty <= 3)
            {
                game->ai_difficulty = difficulty - 1;
                start_game(game, MODE_PVE);
                printf("人机对战模式！难度: %s\n",
                       difficulty == 1 ? "简单" : difficulty == 2 ? "中等"
                                                                  : "困难");
                printf("请在SDL窗口中使用鼠标点击下棋，AI会自动应对\n");
            }
            else
            {
                printf("使用默认难度: 中等\n");
                game->ai_difficulty = MEDIUM;
                start_game(game, MODE_PVE);
                printf("人机对战模式！难度: 中等\n");
                printf("请在SDL窗口中使用鼠标点击下棋，AI会自动应对\n");
            }
            return;
        case 3: // 查看历史记录
            show_history_records();
            break;
        case 4: // 退出
            printf("游戏退出！\n");
            exit(0);
        default:
            printf("无效选择！\n");
        }
    }
}

int main()
{
    // 初始化图形
    if (init_graphics() != 0)
    {
        printf("图形初始化失败！\n");
        return -1;
    }

    Game game;
    init_game(&game);

    // 控制台设置游戏模式
    setup_game(&game);

    printf("\n游戏设置完成！SDL窗口已打开\n");
    printf("使用说明:\n");
    printf("- 在棋盘上点击鼠标左键下棋\n");
    printf("- 黑棋● 先手，白棋○ 后手\n");
    printf("- ESC键返回主菜单\n");
    printf("- 关闭窗口退出游戏\n");

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = 0;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    handle_click(&game, event.button.x, event.button.y);
                }
                break;

            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE)
                {
                    printf("返回主菜单\n");
                    setup_game(&game); // 重新设置游戏
                }
                break;
            }
        }

        // 更新显示
        SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);
        SDL_RenderClear(renderer);
        draw_board(&game.board);
        draw_stones(&game.board);
        SDL_RenderPresent(renderer);
        // 帧率
        SDL_Delay(16);
    }

    cleanup_graphics();
    printf("游戏结束，再见！\n");
    return 0;
}
