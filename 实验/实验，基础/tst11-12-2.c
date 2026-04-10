#include <stdio.h>
int search(int n, int arr[n], int x, int low, int high);
int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    printf("%d", search(n, arr, m, 0, n - 1));

    return 0;
}

int search(int n, int arr[n], int x, int low, int high)
{
    if (low > high)
        return -1;
    else
    {

        int middle = (low + high) / 2;
        if (x > arr[middle])
            search(n, arr, x, low + 1, high);
        else if (x < arr[middle])
            search(n, arr, x, low, middle - 1);
        else
        {
            return middle;
        }
    }
}