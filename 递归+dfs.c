#include <stdio.h>
#include <math.h>

#define MAXN 21

int n, k, ans = 0;
int a[MAXN];

// 判断素数
int is_prime(int x)
{
    if (x < 2)
        return 0;
    int lim = (int)sqrt(x);
    for (int i = 2; i <= lim; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

// DFS 枚举所有组合
void dfs(int idx, int cnt, int sum)
{
    if (cnt == k)
    {
        if (is_prime(sum))
            ans++;
        return;
    }
    if (idx == n)
        return;
    // 选当前数
    dfs(idx + 1, cnt + 1, sum + a[idx]);
    // 不选当前数
    dfs(idx + 1, cnt, sum);
}

int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    dfs(0, 0, 0);
    printf("%d\n", ans);
    return 0;
}
