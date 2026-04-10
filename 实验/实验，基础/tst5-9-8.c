#include <stdio.h>
int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    int low = 0, high = n - 1;
    int middle = (low + high) / 2;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (m > arr[middle])
        {
            low = middle + 1;
        }
        else if (m < arr[middle])
            high = middle - 1;
        else
        {
            printf("%d", middle);
            return 0;
        }
    }

    printf("-1");

    return 0;
}