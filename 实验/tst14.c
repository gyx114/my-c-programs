#include <stdio.h>
#include <stdlib.h>
int **plus(int **a, int a_row, int a_col, int **b, int b_row, int b_col);
int main()
{
    int n;
    scanf("%d", &n);
    int row_and_col[n][2];
    scanf("%d %d", &row_and_col[0][0], &row_and_col[0][1]);
    int ***arrs = (int ***)malloc(n * sizeof(int **));
    arrs[0] = (int **)malloc(row_and_col[0][0] * sizeof(int *));
    for (int i = 0; i < row_and_col[0][0]; i++)
    {
        arrs[0][i] = malloc(row_and_col[0][1] * sizeof(int));
    }

    for (int i = 0; i < row_and_col[0][0]; i++)
    {
        for (int j = 0; j < row_and_col[0][1]; j++)
        {
            scanf("%d", &arrs[0][i][j]);
        }
    }

    int is_cannot_plus = 0;
    // 读取
    for (int k = 1; k < n; k++)
    {
        scanf("%d %d", &row_and_col[k][0], &row_and_col[k][1]);

        if (row_and_col[k][0] != row_and_col[k - 1][1])
        {
            is_cannot_plus = 1;
        }

        arrs[k] = (int **)malloc(row_and_col[k][0] * sizeof(int *));
        for (int i = 0; i < row_and_col[k][0]; i++)
        {
            arrs[k][i] = malloc(row_and_col[k][1] * sizeof(int));
        }

        for (int i = 0; i < row_and_col[k][0]; i++)
        {
            for (int j = 0; j < row_and_col[k][1]; j++)
            {
                scanf("%d", &arrs[k][i][j]);
            }
        }
    }

    // 处理

    if (is_cannot_plus)
    {
        printf("wrong");
    }
    else
    {
        int **tmp = plus(arrs[0], row_and_col[0][0], row_and_col[0][1], arrs[1], row_and_col[1][0], row_and_col[1][1]);
        for (int i = 2; i < n; i++)
        {
            tmp = plus(tmp, row_and_col[0][0], row_and_col[i][0], arrs[i], row_and_col[i][0], row_and_col[i][1]);
        }

        for (int i = 0; i < row_and_col[0][0]; i++)
        {
            for (int j = 0; j < row_and_col[n - 1][1]; j++)
            {
                printf("%d ", tmp[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

int **plus(int **a, int a_row, int a_col, int **b, int b_row, int b_col)
{
    int **ans = (int **)malloc(a_row * sizeof(int *));
    for (int i = 0; i < a_row; i++)
    {
        ans[i] = (int *)malloc(b_col * sizeof(int));
    }

    int sum = 0;
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j++)
        {
            for (int x = 0; x < a_col; x++)
            {
                sum += a[i][x] * b[x][j];
            }
            ans[i][j] = sum;
            sum = 0;
        }
    }

    return ans;
}