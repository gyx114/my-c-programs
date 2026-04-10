#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void free_cheater(int size, int **arr, int x, int y);

int main()
{
    int n;
    scanf("%d", &n);
    int size = (int)pow(2, n);

    int **arr = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        arr[i] = (int *)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 1;
        }
    }

    free_cheater(size, arr, 0, 0);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void free_cheater(int size, int **arr, int x, int y)
{
    if (size == 1)
        return;
    for (int i = x; i < x + size / 2; i++)
    {
        for (int j = y; j < y + size / 2; j++)
        {
            arr[i][j] = 0;
        }
    }
    free_cheater(size / 2, arr, x + size / 2, y);
    free_cheater(size / 2, arr, x, y + size / 2);
    free_cheater(size / 2, arr, x + size / 2, y + size / 2);
}