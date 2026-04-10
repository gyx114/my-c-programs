
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define BOARD_N 10
#define SIZE (BOARD_N * BOARD_N)

enum Square
{
    SQ_EMPTY = 0,
    SQ_WHITE = 1,
    SQ_BLACK = 2,
    SQ_ARROW = 3
};

typedef uint64_t u64;

static int board[SIZE];
static u64 zobrist[SIZE][4];
static u64 zobrist_side;
static u64 hash_key;

typedef struct
{
    unsigned int move;
} Move;

typedef struct
{
    u64 key;
    int depth;
    int value;
    unsigned int move;
    unsigned char flag;
} TTEntry;
static TTEntry *tt = NULL;
static size_t tt_size = 0;

static const int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

static inline int in_board(int x, int y) { return x >= 0 && x < BOARD_N && y >= 0 && y < BOARD_N; }
static inline int idx(int x, int y) { return y * BOARD_N + x; }
static inline void idx_to_xy(int id, int *x, int *y)
{
    *x = id % BOARD_N;
    *y = id / BOARD_N;
}

static u64 rnd_u64()
{
    u64 a = ((u64)rand() << 33) ^ ((u64)rand() << 18) ^ rand();
    a ^= ((u64)rand() << 47) ^ ((u64)rand() << 5);
    return a | 1ULL;
}

static void init_zobrist()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < SIZE; i++)
        for (int s = 0; s < 4; s++)
            zobrist[i][s] = rnd_u64();
    zobrist_side = rnd_u64();
}

static void init_board()
{
    for (int i = 0; i < SIZE; i++)
        board[i] = SQ_EMPTY;
    int whites[] = {3, 6, 30, 33};
    int blacks[] = {66, 69, 93, 96};
    for (int i = 0; i < 4; i++)
        board[whites[i]] = SQ_WHITE;
    for (int i = 0; i < 4; i++)
        board[blacks[i]] = SQ_BLACK;
    hash_key = 0;
    for (int i = 0; i < SIZE; i++)
        if (board[i])
            hash_key ^= zobrist[i][board[i]];
}

static void tt_init(size_t entries)
{
    tt = (TTEntry *)malloc(sizeof(TTEntry) * entries);
    if (!tt)
    {
        tt_size = 0;
        return;
    }
    tt_size = entries;
    for (size_t i = 0; i < entries; i++)
        tt[i].key = 0;
}

static inline unsigned int pack_move(int from, int to, int arrow) { return (from & 0x7F) | ((to & 0x7F) << 7) | ((arrow & 0x7F) << 14); }
static inline void unpack_move(unsigned int m, int *from, int *to, int *arrow)
{
    *from = m & 0x7F;
    *to = (m >> 7) & 0x7F;
    *arrow = (m >> 14) & 0x7F;
}

typedef struct
{
    int from, to, arrow;
    int prev_from, prev_to;
} MoveRecord;
static MoveRecord history[256];
static int hist_sz = 0;

static inline void do_move(unsigned int mv)
{
    int from, to, arrow;
    unpack_move(mv, &from, &to, &arrow);
    history[hist_sz].from = from;
    history[hist_sz].to = to;
    history[hist_sz].arrow = arrow;
    history[hist_sz].prev_from = board[from];
    history[hist_sz].prev_to = board[to];
    hist_sz++;
    int mover = history[hist_sz - 1].prev_from;
    hash_key ^= zobrist[from][mover];
    board[from] = SQ_EMPTY;
    hash_key ^= zobrist[to][history[hist_sz - 1].prev_to];
    board[to] = mover;
    hash_key ^= zobrist[to][mover];
    hash_key ^= zobrist[arrow][board[arrow]];
    board[arrow] = SQ_ARROW;
    hash_key ^= zobrist[arrow][SQ_ARROW];
    hash_key ^= zobrist_side;
}

static inline void undo_move()
{
    hist_sz--;
    int from = history[hist_sz].from;
    int to = history[hist_sz].to;
    int arrow = history[hist_sz].arrow;
    int mover = history[hist_sz].prev_from;
    hash_key ^= zobrist_side;
    hash_key ^= zobrist[arrow][board[arrow]];
    board[arrow] = 0;
    hash_key ^= zobrist[to][board[to]];
    board[to] = history[hist_sz].prev_to;
    if (board[to])
        hash_key ^= zobrist[to][board[to]];
    hash_key ^= zobrist[from][board[from]];
    board[from] = mover;
    if (board[from])
        hash_key ^= zobrist[from][board[from]];
}

static unsigned int moves_buf[1 << 20];

static int generate_moves_for_side(int side, unsigned int *out_moves)
{
    int count = 0;
    for (int pos = 0; pos < SIZE; pos++)
        if (board[pos] == (side == 1 ? SQ_WHITE : SQ_BLACK))
        {
            int x, y;
            idx_to_xy(pos, &x, &y);
            for (int d = 0; d < 8; d++)
            {
                int nx = x + directions[d][0], ny = y + directions[d][1];
                while (in_board(nx, ny) && board[idx(nx, ny)] == SQ_EMPTY)
                {
                    int to = idx(nx, ny);
                    board[pos] = SQ_EMPTY;
                    board[to] = (side == 1 ? SQ_WHITE : SQ_BLACK);
                    int ax, ay;
                    for (int sd = 0; sd < 8; sd++)
                    {
                        ax = nx + directions[sd][0];
                        ay = ny + directions[sd][1];
                        while (in_board(ax, ay) && board[idx(ax, ay)] == SQ_EMPTY)
                        {
                            int arrow = idx(ax, ay);
                            out_moves[count++] = pack_move(pos, to, arrow);
                            ax += directions[sd][0];
                            ay += directions[sd][1];
                        }
                    }
                    board[pos] = (side == 1 ? SQ_WHITE : SQ_BLACK);
                    board[to] = SQ_EMPTY;
                    nx += directions[d][0];
                    ny += directions[d][1];
                }
            }
        }
    return count;
}

static int mobility(int side)
{
    unsigned int tmp[1 << 12];
    return generate_moves_for_side(side, tmp);
}

static int evaluate(int side)
{
    int my = mobility(side);
    int opp = mobility(3 - side);
    return my - opp;
}

#define INF 1000000000

static int alpha_beta(int side, int depth, int alpha, int beta)
{
    if (depth == 0)
        return evaluate(side);
    size_t idx_tt = (tt_size ? (size_t)(hash_key % tt_size) : 0);
    if (tt && tt[idx_tt].key == hash_key && tt[idx_tt].depth >= depth)
    {
        int val = tt[idx_tt].value;
        if (tt[idx_tt].flag == 0)
            return val;
        if (tt[idx_tt].flag == 1)
            alpha = (alpha > val ? alpha : val);
        if (tt[idx_tt].flag == 2)
            beta = (beta < val ? beta : val);
        if (alpha >= beta)
            return val;
    }
    unsigned int *mvbuf = moves_buf;
    int n = generate_moves_for_side(side, mvbuf);
    if (n == 0)
        return -INF + depth;
    int best = -INF;
    for (int i = 0; i < n; i++)
    {
        do_move(mvbuf[i]);
        int val = -alpha_beta(3 - side, depth - 1, -beta, -alpha);
        undo_move();
        if (val > best)
            best = val;
        if (val > alpha)
            alpha = val;
        if (alpha >= beta)
            break;
    }
    if (tt)
    {
        tt[idx_tt].key = hash_key;
        tt[idx_tt].depth = depth;
        tt[idx_tt].value = best;
        tt[idx_tt].move = (n ? mvbuf[0] : 0);
        if (best <= alpha)
            tt[idx_tt].flag = 1;
        else if (best >= beta)
            tt[idx_tt].flag = 2;
        else
            tt[idx_tt].flag = 0;
    }
    return best;
}

static unsigned int search_best(int side, int maxdepth)
{
    unsigned int best_move = 0;
    for (int d = 1; d <= maxdepth; d++)
    {
        unsigned int *mvbuf = moves_buf;
        int n = generate_moves_for_side(side, mvbuf);
        int bestv = -INF;
        for (int i = 0; i < n; i++)
        {
            do_move(mvbuf[i]);
            int val = -alpha_beta(3 - side, d - 1, -INF, INF);
            undo_move();
            if (val > bestv)
            {
                bestv = val;
                best_move = mvbuf[i];
            }
        }
    }
    return best_move;
}

static void print_board()
{
    printf("   a b c d e f g h i j\n");
    for (int y = 0; y < BOARD_N; y++)
    {
        printf("%2d ", y + 1);
        for (int x = 0; x < BOARD_N; x++)
        {
            int v = board[idx(x, y)];
            char c = '.';
            if (v == SQ_WHITE)
                c = 'W';
            else if (v == SQ_BLACK)
                c = 'B';
            else if (v == SQ_ARROW)
                c = 'X';
            printf("%c ", c);
        }
        printf("\n");
    }
}

static int parse_coord(const char *s)
{
    if (!s || strlen(s) < 2)
        return -1;
    int x = s[0] - 'a';
    int y = atoi(s + 1) - 1;
    if (x < 0 || x >= BOARD_N || y < 0 || y >= BOARD_N)
        return -1;
    return idx(x, y);
}

static void coords_from_idx(int id, char *out)
{
    int x, y;
    idx_to_xy(id, &x, &y);
    sprintf(out, "%c%d", 'a' + x, y + 1);
}

int main(int argc, char **argv)
{
    init_zobrist();
    init_board();
    tt_init(1 << 18);
    int side = 1;
    int maxdepth = 3;
    if (argc > 1)
        maxdepth = atoi(argv[1]);
    printf("亚马逊棋 简易引擎。默认白方(人)先行，黑方(电脑)。搜索深度 = %d\n", maxdepth);
    while (1)
    {
        print_board();
        if (side == 1)
        {
            printf("请输入走法：from to arrow（例如 a4 b6 c3）或 q 退出:\n");
            char line[128];
            char a[32], b[32], c[32];
            if (!fgets(line, sizeof(line), stdin))
                break;
            if (line[0] == 'q')
                break;
            int items = sscanf(line, "%s %s %s", a, b, c);
            if (items < 3)
            {
                printf("格式错误\n");
                continue;
            }
            int f = parse_coord(a);
            int t = parse_coord(b);
            int ar = parse_coord(c);
            if (f < 0 || t < 0 || ar < 0)
            {
                printf("坐标无效\n");
                continue;
            }
            unsigned int mv = pack_move(f, t, ar);
            unsigned int tmp[1 << 12];
            int n = generate_moves_for_side(side, tmp);
            int ok = 0;
            for (int i = 0; i < n; i++)
                if (tmp[i] == mv)
                {
                    ok = 1;
                    break;
                }
            if (!ok)
            {
                printf("该着不合法\n");
                continue;
            }
            do_move(mv);
        }
        else
        {
            printf("电脑正在思考 (深度 %d)...\n", maxdepth);
            unsigned int mv = search_best(side, maxdepth);
            if (mv == 0)
            {
                printf("电脑无子可动，游戏结束。\n");
                break;
            }
            int f, t, ar;
            unpack_move(mv, &f, &t, &ar);
            char fs[8], ts[8], as[8];
            coords_from_idx(f, fs);
            coords_from_idx(t, ts);
            coords_from_idx(ar, as);
            printf("电脑走：%s -> %s 射箭 %s\n", fs, ts, as);
            do_move(mv);
        }
        side = 3 - side;
    }
    printf("退出\n");
    return 0;
}
