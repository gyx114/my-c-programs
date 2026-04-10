#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, max_weight;
    scanf("%d %d", &n, &max_weight);
    int weights[n];
    int values[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", weights + i, values + i);
    }

    // 动态规划填表，获得最优解
    int dp[n + 1][max_weight + 1];
    for (int i = 0; i < max_weight + 1; i++)
    {
        dp[0][i] = 0;
    }
    for (int i = 0; i < n + 1; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < max_weight + 1; j++)
        {
            if (j >= weights[i - 1])
            {
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // 回溯挑选的物品
    int is_picked[n];
    int j = max_weight;

    for (int i = n; i > 0;)
    {
        if (dp[i][j] == dp[i - 1][j])
        {
            // 由(i,j)→(i-1,j)
            is_picked[i - 1] = 0;
            i = i - 1;
            j = j;
        }
        else
        {
            // 由(i,j)→(i-1,j-weights[i-1])
            is_picked[i - 1] = 1;
            j = j - weights[i - 1];
            i = i - 1;
        }
    }

    // 输出最大价值
    printf("%d\n", dp[n][max_weight]);

    // 输出选择情况
    for (int i = 0; i < n; i++)
    {
        printf("%d ", is_picked[i]);
    }

    return 0;
}
