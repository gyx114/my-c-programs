#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "game.h"
#include "ai.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// 圆形绘制函数
void draw_circle(int center_x, int center_y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, center_x + dx, center_y + dy);
            }
        }
    }
}

void draw_circle_stone(int x, int y, int player)
{
    int px = BOARD_MARGIN + x * CELL_SIZE;
    int py = BOARD_MARGIN + y * CELL_SIZE;
    int radius = CELL_SIZE / 2 - 2;

    if (player == BLACK)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        draw_circle(px, py, radius);

        // 添加高光效果
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        draw_circle(px - radius / 3, py - radius / 3, radius / 4);
    }
    else if (player == WHITE)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_circle(px, py, radius);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int r = radius; r <= radius + 1; r++)
        {
            for (int angle = 0; angle < 360; angle += 2)
            {
                float rad = angle * 3.14159f / 180.0f;
                int dx = px + (int)(r * cosf(rad));
                int dy = py + (int)(r * sinf(rad));
                SDL_RenderPoint(renderer, dx, dy);
            }
        }
    }
}

int init_graphics(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL3初始化失败\n");
        return -1;
    }

    window = SDL_CreateWindow("六子棋", 800, 600, 0);
    if (!window)
    {
        printf("窗口创建失败: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void cleanup_graphics(void)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_board(const Board *board)
{
    (void)board;

    // 设置棋盘背景色
    SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);
    SDL_RenderClear(renderer);

    // 画棋盘线
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // 横线
        SDL_FRect h_line;
        h_line.x = BOARD_MARGIN;
        h_line.y = BOARD_MARGIN + i * CELL_SIZE - 1;
        h_line.w = (BOARD_SIZE - 1) * CELL_SIZE;
        h_line.h = 2;
        SDL_RenderFillRect(renderer, &h_line);

        // 竖线
        SDL_FRect v_line;
        v_line.x = BOARD_MARGIN + i * CELL_SIZE - 1;
        v_line.y = BOARD_MARGIN;
        v_line.w = 2;
        v_line.h = (BOARD_SIZE - 1) * CELL_SIZE;
        SDL_RenderFillRect(renderer, &v_line);
    }

    // 画天元和星位
    int star_points[5][2] = {{3, 3}, {3, 11}, {7, 7}, {11, 3}, {11, 11}};
    for (int i = 0; i < 5; i++)
    {
        int x = BOARD_MARGIN + star_points[i][0] * CELL_SIZE - 2;
        int y = BOARD_MARGIN + star_points[i][1] * CELL_SIZE - 2;
        SDL_FRect star;
        star.x = x;
        star.y = y;
        star.w = 4;
        star.h = 4;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &star);
    }
}

void draw_stones(const Board *board)
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (board->grid[x][y] != EMPTY)
            {
                draw_circle_stone(x, y, board->grid[x][y]);
            }
        }
    }
}

int get_board_coord(int pixel)
{
    int coord = (pixel - BOARD_MARGIN + CELL_SIZE / 2) / CELL_SIZE;
    if (coord < 0)
        return 0;
    if (coord >= BOARD_SIZE)
        return BOARD_SIZE - 1;
    return coord;
}

void handle_click(Game *game, int mouse_x, int mouse_y)
{
    if (game->state != PLAYING)
        return;

    // PVE模式下，如果是AI回合则不处理玩家点击
    if (game->game_mode == MODE_PVE && game->board.current_player == WHITE)
    {
        return;
    }

    int board_x = get_board_coord(mouse_x);
    int board_y = get_board_coord(mouse_y);

    printf("点击位置: 像素(%d, %d) -> 棋盘(%d, %d)\n", mouse_x, mouse_y, board_x, board_y);

    if (board_x >= 0 && board_x < BOARD_SIZE &&
        board_y >= 0 && board_y < BOARD_SIZE)
    {

        // 玩家下棋
        make_game_move(game, board_x, board_y);

        // PVE模式下，玩家下完后让AI下
        if (game->state == PLAYING && game->game_mode == MODE_PVE &&
            game->board.current_player == WHITE)
        {
            printf("AI思考中...\n");
            Position ai_move = ai_make_move(&game->board, game->ai_difficulty);
            make_game_move(game, ai_move.x, ai_move.y);
            printf("AI落子: (%d, %d)\n", ai_move.x, ai_move.y);
        }

        // 检查游戏是否结束
        if (game->state == GAME_OVER)
        {
            const char *winner = (game->current_record.winner == BLACK) ? "黑棋" : (game->current_record.winner == WHITE) ? "白棋"
                                                                                                                          : "平局";
            printf("游戏结束！%s胜利！\n", winner);
            printf("按ESC键返回主菜单\n");
        }
    }
}
