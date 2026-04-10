//////////////////////////////亚马逊棋游戏 - 完整修复版

#define UNICODE
#define _UNICODE
#define NOMINMAX

#include <tchar.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>
#include <chrono>
#include <queue>
#include <graphics.h>
#include <windows.h>

using namespace std;

// ==================== 常量定义 ====================
const int BOARD_SIZE = 8;
const int AI_SEARCH_DEPTH = 2;
const int CELL_SIZE = 60;
const int BOARD_PADDING = 30;
const int WINDOW_SIZE = BOARD_SIZE * CELL_SIZE + 2 * BOARD_PADDING;
const int BUTTON_WIDTH = 120;
const int BUTTON_HEIGHT = 40;
const int BUTTON_GAP = 20;
const int BUTTON_AREA_X = WINDOW_SIZE + 20;
const int BUTTON_AREA_Y = 50;
const string SAVE_FILE_NAME = "amazons_save.dat";

// ==================== 类型定义 ====================
enum Piece
{
    EMPTY = 0,
    WHITE_QUEEN,
    BLACK_QUEEN,
    ARROW
};

struct Position
{
    int row, col;
    bool operator==(const Position &other) const
    {
        return row == other.row && col == other.col;
    }
};

struct Move
{
    Position queen_start, queen_end, arrow_pos;
};

struct Button
{
    int x, y, w, h;
    const wchar_t *text;
};

typedef vector<vector<int>> Board;

// 将调试输出写入 UTF-8 日志文件，避免依赖控制台编码
void logDebug(const string &msg)
{
    ofstream ofs("amazons_debug.log", ios::app | ios::binary);
    if (!ofs.is_open())
        return;
    // 源文件为 UTF-8，直接写入字节即可
    ofs << msg << "\n";
}

// 在图形窗口底部短暂显示一条信息，替代控制台输出的用户提示
void showTempMessage(const wchar_t *msg, int ms = 800)
{
    setfillcolor(WHITE);
    solidrectangle(0, WINDOW_SIZE - 40, WINDOW_SIZE, WINDOW_SIZE);
    settextcolor(BLACK);
    settextstyle(18, 0, _T("宋体"));
    outtextxy(10, WINDOW_SIZE - 30, (TCHAR *)msg);
    FlushBatchDraw();
    Sleep(ms);
    // 清除消息
    setfillcolor(WHITE);
    solidrectangle(0, WINDOW_SIZE - 40, WINDOW_SIZE, WINDOW_SIZE);
    FlushBatchDraw();
}

// ==================== 全局变量 ====================
vector<Button> buttons = {
    {BUTTON_AREA_X, BUTTON_AREA_Y + 0 * (BUTTON_HEIGHT + BUTTON_GAP),
     BUTTON_WIDTH, BUTTON_HEIGHT, L"存盘"},
    {BUTTON_AREA_X, BUTTON_AREA_Y + 1 * (BUTTON_HEIGHT + BUTTON_GAP),
     BUTTON_WIDTH, BUTTON_HEIGHT, L"读盘"},
    {BUTTON_AREA_X, BUTTON_AREA_Y + 2 * (BUTTON_HEIGHT + BUTTON_GAP),
     BUTTON_WIDTH, BUTTON_HEIGHT, L"新游戏"},
    {BUTTON_AREA_X, BUTTON_AREA_Y + 3 * (BUTTON_HEIGHT + BUTTON_GAP),
     BUTTON_WIDTH, BUTTON_HEIGHT, L"结束游戏"}};

// ==================== 基础函数 ====================
bool isInside(int r, int c)
{
    return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

Board initializeBoard()
{
    Board board(BOARD_SIZE, vector<int>(BOARD_SIZE, EMPTY));
    board[0][2] = WHITE_QUEEN;
    board[0][5] = WHITE_QUEEN;
    board[2][0] = WHITE_QUEEN;
    board[2][7] = WHITE_QUEEN;
    board[7][2] = BLACK_QUEEN;
    board[7][5] = BLACK_QUEEN;
    board[5][0] = BLACK_QUEEN;
    board[5][7] = BLACK_QUEEN;
    return board;
}

// ==================== 路径检查 ====================
bool isMovePathValid(const Position &start, const Position &end,
                     const Board &board, const Position &ignore_pos = {-1, -1})
{
    if (start == end)
        return false;

    int dr = end.row - start.row;
    int dc = end.col - start.col;

    // 必须是直线或斜线
    if (!(dr == 0 || dc == 0 || abs(dr) == abs(dc)))
        return false;

    int step_r = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int step_c = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

    int r = start.row + step_r;
    int c = start.col + step_c;

    // 检查路径上的每个格子（不包括起点和终点）
    while (r != end.row || c != end.col)
    {
        if (!isInside(r, c))
            return false;

        // 允许经过忽略位置（通常是箭的起点）
        if (board[r][c] != EMPTY &&
            !(r == ignore_pos.row && c == ignore_pos.col))
        {
            return false;
        }

        r += step_r;
        c += step_c;
    }

    // 检查终点
    // 终点可以是空的，也可以是指定的忽略位置
    if (board[end.row][end.col] != EMPTY &&
        !(end.row == ignore_pos.row && end.col == ignore_pos.col))
    {
        return false;
    }

    return true;
}

// ==================== 移动操作 ====================
void makeMove(Board &board, const Move &move, Piece current_player, bool execute = true)
{
    if (execute)
    {
        // 写入日志，避免控制台编码/缓冲问题
        logDebug(string("执行移动: 从 (") + to_string(move.queen_start.row) + "," + to_string(move.queen_start.col) + ") 到 (" + to_string(move.queen_end.row) + "," + to_string(move.queen_end.col) + "), 箭在 (" + to_string(move.arrow_pos.row) + "," + to_string(move.arrow_pos.col) + ")");
    }

    board[move.queen_start.row][move.queen_start.col] = EMPTY;
    board[move.queen_end.row][move.queen_end.col] = current_player;
    board[move.arrow_pos.row][move.arrow_pos.col] = ARROW;
}

void undoMove(Board &board, const Move &move, Piece current_player)
{
    board[move.queen_end.row][move.queen_end.col] = EMPTY;
    board[move.queen_start.row][move.queen_start.col] = current_player;
    board[move.arrow_pos.row][move.arrow_pos.col] = EMPTY;
}

// ==================== 移动验证 ====================
bool isMoveValid(const Move &move, const Board &board, Piece current_player)
{
    if (!isInside(move.queen_start.row, move.queen_start.col) ||
        !isInside(move.queen_end.row, move.queen_end.col) ||
        !isInside(move.arrow_pos.row, move.arrow_pos.col))
        return false;

    if (board[move.queen_start.row][move.queen_start.col] != current_player)
        return false;

    if (!isMovePathValid(move.queen_start, move.queen_end, board))
        return false;

    // 箭位在原棋盘上可以是空，或者正好等于皇后起点（因为皇后会腾空该格）
    if (board[move.arrow_pos.row][move.arrow_pos.col] != EMPTY)
    {
        if (!(move.arrow_pos == move.queen_start))
            return false;
    }

    Board temp_board = board;
    temp_board[move.queen_start.row][move.queen_start.col] = EMPTY;
    temp_board[move.queen_end.row][move.queen_end.col] = current_player;

    if (!isMovePathValid(move.queen_end, move.arrow_pos, temp_board, move.queen_end))
        return false;

    return true;
}

// ==================== 移动生成 ====================
vector<Move> getValidMovesForQueen(const Position &start_pos, const Board &board, Piece current_player)
{
    vector<Move> valid_moves;
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

    if (board[start_pos.row][start_pos.col] != current_player)
        return valid_moves;

    for (int i = 0; i < 8; ++i)
    {
        int dr = directions[i][0], dc = directions[i][1];
        for (int step = 1;; ++step)
        {
            Position queen_end = {start_pos.row + dr * step, start_pos.col + dc * step};
            if (!isInside(queen_end.row, queen_end.col))
                break;
            if (!isMovePathValid(start_pos, queen_end, board))
                break;

            Board temp_board = board;
            temp_board[start_pos.row][start_pos.col] = EMPTY;
            temp_board[queen_end.row][queen_end.col] = current_player;

            for (int j = 0; j < 8; ++j)
            {
                int ar = directions[j][0], ac = directions[j][1];
                for (int arrow_step = 1;; ++arrow_step)
                {
                    Position arrow_pos = {queen_end.row + ar * arrow_step,
                                          queen_end.col + ac * arrow_step};
                    if (!isInside(arrow_pos.row, arrow_pos.col))
                        break;
                    if (isMovePathValid(queen_end, arrow_pos, temp_board, queen_end))
                        valid_moves.push_back({start_pos, queen_end, arrow_pos});
                    else
                        break;
                }
            }
        }
    }
    return valid_moves;
}

vector<Move> getAllValidMoves(const Board &board, Piece current_player)
{
    vector<Move> all_moves;
    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            if (board[r][c] == current_player)
            {
                Position queen_pos = {r, c};
                vector<Move> queen_moves = getValidMovesForQueen(queen_pos, board, current_player);
                all_moves.insert(all_moves.end(), queen_moves.begin(), queen_moves.end());
            }
        }
    }
    return all_moves;
}

bool checkGameOver(const Board &board, Piece current_player)
{
    return getAllValidMoves(board, current_player).empty();
}

// ==================== 存档功能 ====================
bool saveGame(const Board &board, Piece currentPlayer)
{
    ofstream outFile(SAVE_FILE_NAME);
    if (!outFile.is_open())
    {
        cerr << "错误：无法打开文件 " << SAVE_FILE_NAME << " 进行保存。" << endl;
        return false;
    }
    outFile << BOARD_SIZE << endl
            << (int)currentPlayer << endl;
    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
            outFile << board[r][c] << " ";
        outFile << endl;
    }
    outFile.close();
    logDebug(string("游戏已成功保存到文件: ") + SAVE_FILE_NAME);
    return true;
}

bool loadGame(Board &board, Piece &currentPlayer)
{
    ifstream inFile(SAVE_FILE_NAME);
    if (!inFile.is_open())
    {
        showTempMessage(L"提示：找不到存档文件，将开始新游戏。", 1000);
        return false;
    }
    int loaded_size, loaded_player_int;
    inFile >> loaded_size;
    if (loaded_size != BOARD_SIZE)
    {
        cerr << "错误：存档文件中的棋盘大小不匹配 (" << loaded_size << ")。" << endl;
        inFile.close();
        return false;
    }
    inFile >> loaded_player_int;
    currentPlayer = (Piece)loaded_player_int;
    Board loaded_board(BOARD_SIZE, vector<int>(BOARD_SIZE));
    for (int r = 0; r < BOARD_SIZE; ++r)
        for (int c = 0; c < BOARD_SIZE; ++c)
            if (!(inFile >> loaded_board[r][c]))
            {
                cerr << "错误：读取棋盘数据失败。" << endl;
                inFile.close();
                return false;
            }
    inFile.close();
    board = loaded_board;
    showTempMessage(L"游戏已成功从存档加载。", 1000);
    return true;
}

// ==================== 图形界面 ====================
void drawButtons()
{
    settextstyle(20, 0, _T("宋体"));
    for (const auto &btn : buttons)
    {
        setlinecolor(BLACK);
        setfillcolor(RGB(220, 220, 220));
        fillrectangle(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h);
        settextcolor(BLACK);
        outtextxy(btn.x + 15, btn.y + 10, (TCHAR *)btn.text);
    }
}

void printBoardGraphics(const Board &board)
{
    cleardevice();

    // 绘制棋盘格子
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            int left = BOARD_PADDING + c * CELL_SIZE;
            int top = BOARD_PADDING + r * CELL_SIZE;
            COLORREF cellColor = ((r + c) % 2 == 0) ? RGB(240, 217, 181) : RGB(181, 136, 99);
            setfillcolor(cellColor);
            solidrectangle(left, top, left + CELL_SIZE, top + CELL_SIZE);
        }
    }

    // 绘制棋盘线
    setlinecolor(DARKGRAY);
    setlinestyle(PS_SOLID, 2);
    for (int i = 0; i <= BOARD_SIZE; ++i)
    {
        int pos = BOARD_PADDING + i * CELL_SIZE;
        line(BOARD_PADDING, pos, WINDOW_SIZE - BOARD_PADDING, pos);
        line(pos, BOARD_PADDING, pos, WINDOW_SIZE - BOARD_PADDING);
    }

    // 绘制棋子和箭
    for (int r = 0; r < BOARD_SIZE; r++)
    {
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            int center_x = BOARD_PADDING + c * CELL_SIZE + CELL_SIZE / 2;
            int center_y = BOARD_PADDING + r * CELL_SIZE + CELL_SIZE / 2;
            int radius = CELL_SIZE / 3;

            switch (board[r][c])
            {
            case WHITE_QUEEN:
                setfillcolor(RGB(220, 220, 220));
                fillcircle(center_x, center_y, radius);
                setfillcolor(RGB(255, 255, 255));
                solidcircle(center_x - radius / 3, center_y - radius / 3, radius / 2);
                break;
            case BLACK_QUEEN:
                setfillcolor(RGB(40, 40, 40));
                fillcircle(center_x, center_y, radius);
                setfillcolor(RGB(180, 180, 180));
                solidcircle(center_x - radius / 3, center_y - radius / 3, radius / 2);
                break;
            case ARROW:
                setfillcolor(RGB(100, 100, 100));
                fillcircle(center_x, center_y, radius);
                setfillcolor(RGB(180, 180, 180));
                solidcircle(center_x - radius / 3, center_y - radius / 3, radius / 2);
                break;
            }
        }
    }

    // 绘制状态文本
    settextcolor(BLACK);
    settextstyle(20, 0, _T("宋体"));
    outtextxy(10, WINDOW_SIZE - 25, _T("请在棋盘窗口操作按钮或走棋"));

    drawButtons();
}

void drawHighlight(Position p, COLORREF color)
{
    int left = BOARD_PADDING + p.col * CELL_SIZE;
    int top = BOARD_PADDING + p.row * CELL_SIZE;
    setfillcolor(color);
    solidrectangle(left + 1, top + 1, left + CELL_SIZE - 4, top + CELL_SIZE - 4);
}

void animateMove(const Position &start, const Position &end, Piece piece, const Board &board)
{
    int steps = 10;
    int sx = BOARD_PADDING + start.col * CELL_SIZE + CELL_SIZE / 2;
    int sy = BOARD_PADDING + start.row * CELL_SIZE + CELL_SIZE / 2;
    int ex = BOARD_PADDING + end.col * CELL_SIZE + CELL_SIZE / 2;
    int ey = BOARD_PADDING + end.row * CELL_SIZE + CELL_SIZE / 2;

    for (int i = 1; i <= steps; ++i)
    {
        double t = i / (double)steps;
        int x = sx + (ex - sx) * t;
        int y = sy + (ey - sy) * t;
        printBoardGraphics(board);

        int radius = CELL_SIZE / 3;
        if (piece == WHITE_QUEEN)
        {
            setfillcolor(RGB(220, 220, 220));
            fillcircle(x, y, radius);
        }
        else
        {
            setfillcolor(RGB(40, 40, 40));
            fillcircle(x, y, radius);
        }
        FlushBatchDraw();
        Sleep(20);
    }
}

// ==================== 特效 ====================
void showFireworks()
{
    int cx = WINDOW_SIZE / 2, cy = WINDOW_SIZE / 2;
    for (int t = 0; t < 30; ++t)
    {
        for (int i = 0; i < 40; ++i)
        {
            double angle = rand() * 2 * 3.14159 / RAND_MAX;
            int r = 30 + t * 4;
            int x = cx + (int)(r * cos(angle));
            int y = cy + (int)(r * sin(angle));
            setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
            solidcircle(x, y, 4);
        }
        FlushBatchDraw();
        Sleep(30);
    }
}

void showBlinkText(const wchar_t *text, int x, int y)
{
    for (int i = 0; i < 8; ++i)
    {
        settextcolor(i % 2 == 0 ? RED : RGB(255, 215, 0));
        settextstyle(40, 0, _T("宋体"));
        outtextxy(x, y, (TCHAR *)text);
        FlushBatchDraw();
        Sleep(200);
        setfillcolor(WHITE);
        solidrectangle(x, y, x + 400, y + 50);
    }
}

// ==================== 用户输入 ====================
Position getClickPosition()
{
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            int click_x = m.x, click_y = m.y;
            if (click_x >= BOARD_PADDING && click_x < WINDOW_SIZE - BOARD_PADDING &&
                click_y >= BOARD_PADDING && click_y < WINDOW_SIZE - BOARD_PADDING)
            {
                int c = (click_x - BOARD_PADDING) / CELL_SIZE;
                int r = (click_y - BOARD_PADDING) / CELL_SIZE;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE)
                    return {r, c};
            }
            return {-1, -1};
        }
    }
}

int getButtonClick(const MOUSEMSG &m)
{
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        const auto &btn = buttons[i];
        if (m.x >= btn.x && m.x <= btn.x + btn.w &&
            m.y >= btn.y && m.y <= btn.y + btn.h)
            return (int)i;
    }
    return -1;
}

// ==================== 玩家操作 ====================
Move getPlayerMoveByClick(const Board &board, Piece current_player)
{
    Move move;
    Position p = {-1, -1};
    int step = 1;
    vector<Move> all_possible_moves;

    BeginBatchDraw();

    while (step <= 3)
    {
        printBoardGraphics(board);
        settextcolor(BLACK);

        if (step == 2)
        {
            settextstyle(20, 0, _T("宋体"));
            outtextxy(10, WINDOW_SIZE - 25, _T("2/3: 请点击皇后目标"));
            for (const auto &m : all_possible_moves)
                drawHighlight(m.queen_end, RGB(196, 168, 143));
        }
        else if (step == 3)
        {
            settextstyle(20, 0, _T("宋体"));
            outtextxy(10, WINDOW_SIZE - 25, _T("3/3: 请点击射箭目标"));
            for (const auto &m : all_possible_moves)
                if (m.queen_end == move.queen_end)
                    drawHighlight(m.arrow_pos, RGB(138, 51, 36));
        }

        FlushBatchDraw();

        MOUSEMSG m = GetMouseMsg();
        int btnIdx = getButtonClick(m);

        if (btnIdx != -1 && m.uMsg == WM_LBUTTONDOWN)
        {
            EndBatchDraw();
            if (btnIdx == 3)
                return {{-1, -1}, {-1, -1}, {-1, -1}};
            if (btnIdx == 0)
            {
                saveGame(board, current_player);
                continue;
            }
            if (btnIdx == 1)
                return {{-2, -2}, {-2, -2}, {-2, -2}};
            if (btnIdx == 2)
                return {{-3, -3}, {-3, -3}, {-3, -3}};
            continue;
        }

        if (m.uMsg == WM_LBUTTONDOWN)
        {
            int click_x = m.x, click_y = m.y;
            if (click_x >= BOARD_PADDING && click_x < WINDOW_SIZE - BOARD_PADDING &&
                click_y >= BOARD_PADDING && click_y < WINDOW_SIZE - BOARD_PADDING)
            {
                int c = (click_x - BOARD_PADDING) / CELL_SIZE;
                int r = (click_y - BOARD_PADDING) / CELL_SIZE;
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE)
                    p = {r, c};
                else
                    continue;
            }
            else
                continue;
        }
        else
            continue;

        if (step == 1)
        {
            if (board[p.row][p.col] == current_player)
            {
                move.queen_start = p;
                all_possible_moves = getValidMovesForQueen(move.queen_start, board, current_player);
                if (!all_possible_moves.empty())
                    step = 2;
                else
                    showTempMessage(L"该皇后无移动空间，请选择其他皇后！");
            }
            else
                showTempMessage(L"请选择您的皇后！");
        }
        else if (step == 2)
        {
            bool valid = false;
            for (const auto &m : all_possible_moves)
                if (m.queen_end == p)
                {
                    valid = true;
                    break;
                }
            if (valid)
            {
                move.queen_end = p;
                step = 3;
            }
            else
                showTempMessage(L"目标位置不合法！");
        }
        else if (step == 3)
        {
            move.arrow_pos = p;
            bool found = false;
            for (const auto &m : all_possible_moves)
                if (m.queen_end == move.queen_end && m.arrow_pos == move.arrow_pos)
                {
                    found = true;
                    break;
                }
            if (found)
            {
                EndBatchDraw();
                return move;
            }
            else
            {
                showTempMessage(L"射箭位置不合法！");
                step = 1;
                all_possible_moves.clear();
            }
        }
    }
    EndBatchDraw();
    return move;
}

// ==================== AI逻辑 ====================
int scoreMove(const Board &board, const Move &move, Piece player)
{
    int score = 0;
    Board temp_board = board;
    makeMove(temp_board, move, player, false);
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int i = 0; i < 8; ++i)
    {
        int nr = move.queen_end.row + directions[i][0];
        int nc = move.queen_end.col + directions[i][1];
        if (isInside(nr, nc) && temp_board[nr][nc] == EMPTY)
            score++;
    }
    return score;
}

int evaluateBoard(const Board &board)
{
    int w_mobility = 0, b_mobility = 0;
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int r = 0; r < BOARD_SIZE; ++r)
    {
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            if (board[r][c] == WHITE_QUEEN)
            {
                for (int i = 0; i < 8; ++i)
                {
                    int nr = r + directions[i][0], nc = c + directions[i][1];
                    if (isInside(nr, nc) && board[nr][nc] == EMPTY)
                        w_mobility++;
                }
            }
            else if (board[r][c] == BLACK_QUEEN)
            {
                for (int i = 0; i < 8; ++i)
                {
                    int nr = r + directions[i][0], nc = c + directions[i][1];
                    if (isInside(nr, nc) && board[nr][nc] == EMPTY)
                        b_mobility++;
                }
            }
        }
    }
    return b_mobility - w_mobility;
}

int minimax(Board board, int depth, int alpha, int beta, bool isMaximizingPlayer) // 注意：这里按值传递
{
    Piece currentPlayer = isMaximizingPlayer ? BLACK_QUEEN : WHITE_QUEEN;
    if (depth == 0)
        return evaluateBoard(board);

    vector<Move> possibleMoves = getAllValidMoves(board, currentPlayer);
    if (possibleMoves.empty())
        return isMaximizingPlayer ? -1000000 : 1000000;

    if (isMaximizingPlayer)
    {
        sort(possibleMoves.begin(), possibleMoves.end(),
             [&](const Move &a, const Move &b)
             {
                 return scoreMove(board, a, currentPlayer) > scoreMove(board, b, currentPlayer);
             });
    }

    if (isMaximizingPlayer)
    {
        int maxEval = -1000000;
        for (const Move &move : possibleMoves)
        {
            Board temp_board = board;                         // 创建临时副本
            makeMove(temp_board, move, currentPlayer, false); // 不打印日志
            int eval = minimax(temp_board, depth - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, maxEval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = 1000000;
        for (const Move &move : possibleMoves)
        {
            Board temp_board = board;                         // 创建临时副本
            makeMove(temp_board, move, currentPlayer, false); // 不打印日志
            int eval = minimax(temp_board, depth - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, minEval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

Move findBestMove(const Board &board) // 改为 const 引用
{
    int bestVal = -1000000;
    Move bestMove;
    vector<Move> possibleMoves = getAllValidMoves(board, BLACK_QUEEN);

    sort(possibleMoves.begin(), possibleMoves.end(),
         [&](const Move &a, const Move &b)
         {
             return scoreMove(board, a, BLACK_QUEEN) > scoreMove(board, b, BLACK_QUEEN);
         });

    for (const Move &move : possibleMoves)
    {
        Board temp_board = board;                       // 创建临时副本
        makeMove(temp_board, move, BLACK_QUEEN, false); // 不打印日志
        int moveVal = minimax(temp_board, AI_SEARCH_DEPTH - 1, -1000000, 1000000, false);
        if (moveVal > bestVal)
        {
            bestVal = moveVal;
            bestMove = move;
        }
    }

    logDebug(string("AI 最佳移动评估分数: ") + to_string(bestVal));
    return bestMove;
}

// ==================== 主函数 ====================
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Board board = initializeBoard();

    Piece currentPlayer = WHITE_QUEEN;
    bool game_over = false;

    initgraph(WINDOW_SIZE + BUTTON_WIDTH + 60, WINDOW_SIZE, EW_SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();

    BeginBatchDraw();

    while (!game_over)
    {
        printBoardGraphics(board);
        FlushBatchDraw();

        // ========== 检查当前玩家是否无路可走 ==========
        // 如果当前要走的玩家没有合法走法，则该玩家被困，对手获胜
        if (checkGameOver(board, currentPlayer))
        {
            Piece winner_piece = (currentPlayer == WHITE_QUEEN) ? BLACK_QUEEN : WHITE_QUEEN;
            wchar_t winner = (winner_piece == WHITE_QUEEN) ? L'W' : L'B';
            settextcolor(RED);
            settextstyle(30, 0, _T("宋体"));
            TCHAR win_text[100];
            _stprintf_s(win_text, _T("玩家 %c 获胜！"), winner);
            outtextxy(BOARD_PADDING, WINDOW_SIZE / 2 - 30, win_text);

            // 显示原因信息：哪个玩家被困
            settextstyle(20, 0, _T("宋体"));
            TCHAR reason_text[100];
            _stprintf_s(reason_text, _T("玩家 %c 无路可走"),
                        (currentPlayer == WHITE_QUEEN) ? L'W' : L'B');
            outtextxy(BOARD_PADDING, WINDOW_SIZE / 2 + 10, reason_text);

            // 播放特效
            if (winner == L'W')
            {
                showFireworks();
                showBlinkText(L"恭喜玩家 W 获胜！", BOARD_PADDING, WINDOW_SIZE / 2 + 50);
            }
            else
            {
                showFireworks();
                showBlinkText(L"玩家 B (AI) 获胜！", BOARD_PADDING, WINDOW_SIZE / 2 + 50);
            }

            game_over = true;
            FlushBatchDraw();
            Sleep(3000);

            // 显示提示并等待新游戏或退出
            settextcolor(BLACK);
            settextstyle(20, 0, _T("宋体"));
            outtextxy(BUTTON_AREA_X, BUTTON_AREA_Y + 5 * (BUTTON_HEIGHT + BUTTON_GAP),
                      _T("游戏结束，点击\"新游戏\"可重开"));
            FlushBatchDraw();

            while (game_over)
            {
                MOUSEMSG m = GetMouseMsg();
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    int btnIdx = getButtonClick(m);
                    if (btnIdx == 2) // 新游戏按钮
                    {
                        board = initializeBoard();
                        currentPlayer = WHITE_QUEEN;
                        game_over = false;
                        break;
                    }
                    else if (btnIdx == 3) // 结束游戏按钮
                    {
                        // 直接退出主循环
                        break;
                    }
                }
            }

            if (!game_over)
                continue;
            else
                break;
        }

        if (currentPlayer == WHITE_QUEEN)
        {
            bool waiting = true;
            while (waiting && !game_over)
            {
                MOUSEMSG m = GetMouseMsg();
                int btnIdx = getButtonClick(m);

                if (btnIdx != -1 && m.uMsg == WM_LBUTTONDOWN)
                {
                    if (btnIdx == 0)
                    {
                        saveGame(board, currentPlayer);
                        printBoardGraphics(board);
                        FlushBatchDraw();
                    }
                    else if (btnIdx == 1)
                    {
                        loadGame(board, currentPlayer);
                        printBoardGraphics(board);
                        FlushBatchDraw();
                    }
                    else if (btnIdx == 2)
                    {
                        board = initializeBoard();
                        currentPlayer = WHITE_QUEEN;
                        game_over = false;
                        printBoardGraphics(board);
                        FlushBatchDraw();
                    }
                    else if (btnIdx == 3)
                    {
                        game_over = true;
                        break;
                    }
                }
                else
                {
                    Move playerMove = getPlayerMoveByClick(board, currentPlayer);

                    if (playerMove.queen_start.row == -1) // 结束游戏
                    {
                        game_over = true;
                        break;
                    }
                    if (playerMove.queen_start.row == -2) // 读盘
                    {
                        loadGame(board, currentPlayer);
                        printBoardGraphics(board);
                        FlushBatchDraw();
                        continue;
                    }
                    if (playerMove.queen_start.row == -3) // 新游戏
                    {
                        board = initializeBoard();
                        currentPlayer = WHITE_QUEEN;
                        game_over = false;
                        printBoardGraphics(board);
                        FlushBatchDraw();
                        continue;
                    }

                    if (isMoveValid(playerMove, board, currentPlayer))
                    {
                        animateMove(playerMove.queen_start, playerMove.queen_end, currentPlayer, board);
                        makeMove(board, playerMove, currentPlayer);
                        currentPlayer = BLACK_QUEEN;
                    }
                    waiting = false;
                }
            }
        }
        else
        {
            settextcolor(BLACK);
            settextstyle(20, 0, _T("宋体"));
            outtextxy(BUTTON_AREA_X, BUTTON_AREA_Y + 4 * (BUTTON_HEIGHT + BUTTON_GAP),
                      _T("AI正在思考..."));
            FlushBatchDraw();

            auto start = chrono::high_resolution_clock::now();
            Move aiMove = findBestMove(board); // 不会修改原始棋盘
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            logDebug(string("AI 思考时间: ") + to_string(duration.count()) + " 秒");

            if (aiMove.queen_start.row != -1) // 确保有有效移动
            {
                animateMove(aiMove.queen_start, aiMove.queen_end, currentPlayer, board);
                makeMove(board, aiMove, BLACK_QUEEN);
                currentPlayer = WHITE_QUEEN;
            }
            else
            {
                // AI 无路可走，人类玩家获胜
                settextcolor(RED);
                settextstyle(30, 0, _T("宋体"));
                outtextxy(BOARD_PADDING, WINDOW_SIZE / 2 - 30, _T("玩家 W 获胜！"));
                settextstyle(20, 0, _T("宋体"));
                outtextxy(BOARD_PADDING, WINDOW_SIZE / 2 + 10, _T("AI 无路可走"));
                showFireworks();
                showBlinkText(L"恭喜玩家 W 获胜！", BOARD_PADDING, WINDOW_SIZE / 2 + 50);
                game_over = true;
                FlushBatchDraw();
                Sleep(3000);
            }
        }
    }

    // 最终显示
    if (game_over)
    {
        settextcolor(BLACK);
        settextstyle(20, 0, _T("宋体"));
        outtextxy(BUTTON_AREA_X, BUTTON_AREA_Y + 5 * (BUTTON_HEIGHT + BUTTON_GAP),
                  _T("游戏结束，点击\"新游戏\"可重开"));
        FlushBatchDraw();

        // 等待退出或新游戏
        while (true)
        {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                int btnIdx = getButtonClick(m);
                if (btnIdx == 2) // 新游戏
                {
                    board = initializeBoard();
                    currentPlayer = WHITE_QUEEN;
                    game_over = false;
                    break;
                }
                else if (btnIdx == 3) // 结束游戏
                {
                    break;
                }
            }
        }
    }

    EndBatchDraw();
    closegraph();

    return 0;
}
