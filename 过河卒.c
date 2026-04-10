#include <stdio.h>

long long find(long long a_x, long long a_y, long long b_x, long long b_y, long long ma_x, long long ma_y);
int main()
{

    long long b_x, b_y, ma_x, ma_y;
    scanf("%lld %lld %lld %lld", &b_x, &b_y, &ma_x, &ma_y);
    printf("%lld", find(0, 0, b_x, b_y, ma_x, ma_y));
    return 0;
}

long long find(long long a_x, long long a_y, long long b_x, long long b_y, long long ma_x, long long ma_y)
// 计算(a_x,a_y)出发有几条路，返回dp[a_x,a_y]
{
    static long long dp[21][21] = {0}; // Assuming b_x, b_y <= 20
    static long long visited[21][21] = {0};
    // 关键：通过visited记录是否已填，实现减少计算

    if (a_x > b_x || a_y > b_y)
        return 0;
    long long r2 = (a_x - ma_x) * (a_x - ma_x) + (a_y - ma_y) * (a_y - ma_y);
    if (r2 == 0 || r2 == 5)
        return 0;

    if (a_x == b_x && a_y == b_y)
        return 1;

    if (visited[a_x][a_y])
        return dp[a_x][a_y];

    dp[a_x][a_y] = find(a_x + 1, a_y, b_x, b_y, ma_x, ma_y) + find(a_x, a_y + 1, b_x, b_y, ma_x, ma_y);
    visited[a_x][a_y] = 1;
    return dp[a_x][a_y]; // 记得return！
}
