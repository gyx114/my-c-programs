#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

int search(int n, int **nums, int x, int y)
{
    int dp[n][n];
    int is_visited[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            is_visited[i][j] = 0;
        }
    }
    dp[n - 1][n - 1] = nums[n - 1][n - 1];
    if (x >= n || y >= n)
    {
        return 0;
    }
    else if (x == n - 1)
    {
        int sum = 0;
        for (int i = y; i < n; i++)
        {
            sum += nums[x][i];
        }
        is_visited[x][y] = 1;
        dp[x][y] = sum;
        return sum;
    }

    else if (y == n - 1)
    {
        int sum = 0;
        for (int i = x; i < n; i++)
        {
            sum += nums[i][y];
        }
        is_visited[x][y] = 1;
        dp[x][y] = sum;
        return sum;
    }

    else
    {
        if (is_visited[x][y + 1] && is_visited[x + 1][y])
        {
            dp[x][y] = max(dp[x][y + 1], dp[x + 1][y]) + nums[x][y];
            is_visited[x][y] = 1;
            return dp[x][y];
        }
        else
        {
            dp[x][y] = search(n, nums, x + 1, y) + search(n, nums, x, y + 1);
            is_visited[x][y] = 1;
            return dp[x][y];
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int **nums = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        nums[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &nums[i][j]);
        }
    }
    search(n, nums, 0, 0);
    return 0;
}
