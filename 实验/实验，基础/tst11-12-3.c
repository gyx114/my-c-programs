#include <stdio.h>
int search(int n, int arr[n], int max);
int main()
{

    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    printf("%d", search(n, arr, 0));

    return 0;
}

int search(int n, int arr[n], int max)
{
    if (n == 0)
        return max;
    else
    {
        if (arr[0] > max)
        {
            max = arr[0];
            search(n - 1, arr + 1, max);
        }
        else
            search(n - 1, arr + 1, max);
    }
}