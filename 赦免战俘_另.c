#include <stdio.h>
#include <math.h>
void free_cheater(int full_size, int arr[full_size][full_size], int x, int y, int current_size);

int main()
{

    int n;
    scanf("%d", &n);
    int size = (int)pow(2, n);
    int arr[size][size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 1;
        }
    }
    free_cheater(size, arr, 0, 0, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void free_cheater(int full_size, int arr[full_size][full_size], int x, int y, int current_size)
{
    if (current_size == 1)
        return;
    for (int i = x; i < x + current_size / 2; i++)
    {
        for (int j = y; j < y + current_size / 2; j++)
        {
            arr[i][j] = 0;
        }
    }
    free_cheater(full_size, arr, x + current_size / 2, y, current_size / 2);
    free_cheater(full_size, arr, x, y + current_size / 2, current_size / 2);
    free_cheater(full_size, arr, x + current_size / 2, y + current_size / 2, current_size / 2);
}