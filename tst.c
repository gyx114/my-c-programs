#include <stdio.h>

int search(int *arr, int n)
{

    if (n == 1)
    {
        return arr[0];
    }

    if (search(arr, n / 2) > search(arr + n / 2, n - n / 2))
    {
        return search(arr, n / 2);
    }
    else
    {
        return search(arr + n / 2, n - n / 2);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }
    printf("%d", search(arr, n));
}
