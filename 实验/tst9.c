#include <stdio.h>
#include <math.h>
int f(int x);
int main()
{

    int x;
    scanf("%d", &x);
    printf("%d", f(x));

    return 0;
}

int f(int x)
{

    if (x < -2)
        return (2 * x - 1);
    else if (x >= 0)
    {
        return ((int)sqrt((double)x));
    }

    else
    {
        return x * x;
    }
}