#include <stdio.h>
int main()
{

    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;

    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;

    printf("%d %d %d", min, a + b + c - min - max, max);
    return 0;
}