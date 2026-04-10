#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nums[9][9];
int standard[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int compare(const void *a, const void *b)
{
    return (*((int *)a) - *((int *)b));
}

int is_partially_right(const int *arr)
{
    int tmp[9];
    memcpy(tmp, arr, 9 * sizeof(int));
    qsort(tmp, 9, sizeof(int), compare);
    for (int i = 0; i < 9; i++)
    {
        if (tmp[i] != standard[i])
            return 0;
    }

    return 1;
}

void read_gong(int x, int y, int *arr)
{
    arr[0] = nums[x][y];
    arr[1] = nums[x][y + 1];
    arr[2] = nums[x][y + 2];
    arr[3] = nums[x + 1][y];
    arr[4] = nums[x + 1][y + 1];
    arr[5] = nums[x + 1][y + 2];
    arr[6] = nums[x + 2][y];
    arr[7] = nums[x + 2][y + 1];
    arr[8] = nums[x + 2][y + 2];
}

int is_right()
{

    int *arr = (int *)malloc(9 * sizeof(int));
    if (!arr)
        return 0;
    // 判断行
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arr[j] = nums[i][j];
        }

        if (!is_partially_right(arr))
        {
            free(arr);
            return 0;
        }
    }

    // 判断列
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arr[j] = nums[j][i];
        }

        if (!is_partially_right(arr))
        {
            free(arr);
            return 0;
        }
    }

    // 判断宫
    for (int sx = 0; sx < 9; sx += 3)
    {
        for (int sy = 0; sy < 9; sy += 3)
        {
            read_gong(sx, sy, arr);
            if (!is_partially_right(arr))
            {
                free(arr);
                return 0;
            }
        }
    }

    free(arr);
    return 1;
}

void get_and_analyze()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            scanf("%d", &nums[i][j]);
        }
    }
    printf(is_right() ? "Accepted\n" : "Wrong Answer\n");
}

int main()
{

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        get_and_analyze();
    }

    return 0;
}
