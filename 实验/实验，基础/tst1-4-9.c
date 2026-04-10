#include <stdio.h>
int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    int n = 0;
    while (1)
    {
        if (n % 3 == x && n % 5 == y && n % 7 == z)
        {
            printf("%d", n);
            break;
        }
        else
        {
            n++;
        }
    }

    return 0;
}