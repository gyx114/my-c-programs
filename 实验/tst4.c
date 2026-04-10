#include <stdio.h>

void fill(int n, int m, int current_n, int current_m, int current_x, int current_y, int arr[n][m], int start_num);
int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n][m];

    fill(n, m, n, m, 0, 0, arr, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void fill(int n, int m, int current_n, int current_m, int current_x, int current_y, int arr[n][m], int start_num)
{

    if (current_m <= 0 || current_n <= 0)
        return;
    else
    {

        // 向右
        if (current_m >= 1)
        {
            for (int i = 0; i < current_m; i++)
            {
                arr[current_x][current_y + i] = start_num;
                start_num++;
            }
        }

        if (current_n > 1)
        {
            // 向下
            for (int i = 1; i <= current_n - 1; i++)
            {
                arr[current_x + i][current_y + current_m - 1] = start_num;
                start_num++;
            }
        }
        // 向左，需要保证至少有两行，防止向左覆盖向右
        if (current_m > 1 && current_n > 1)
        {
            for (int i = 0; i < current_m - 1; i++)
            {
                arr[current_x + current_n - 1][current_y + current_m - 2 - i] = start_num;
                start_num++;
            }
        }

        // 向上,需要保证至少有两列，防止向上覆盖向下
        if (current_n > 1 && current_m > 1)
        {
            for (int i = 0; i < current_n - 2; i++)
            {
                arr[current_x + current_n - 2 - i][current_y] = start_num;
                start_num++;
            }
        }
    }

    if (current_n - 2 >= 0 && current_m - 2 >= 0)
    {
        fill(n, m, current_n - 2, current_m - 2, current_x + 1, current_y + 1, arr, start_num);
    }
}