#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }
    int x;
    scanf("%d", &x);
    int y = 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            printf("%d", i);
            y = 0;
            break;
        }
    }
    if (y)
        printf("-1");

    return 0;
}